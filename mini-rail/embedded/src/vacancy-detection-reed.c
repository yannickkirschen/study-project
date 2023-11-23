#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#include <stdbool.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "rail/vacancy.h"

const uint ONBOARD_LED_PIN = 25;

const uint ERROR_UPPER_LED_PIN = 22;
const uint ERROR_MIDDLE_LED_PIN = 21;
const uint ERROR_LOWER_LED_PIN = 20;

const uint OCCUPIED_UPPER_LED_PIN = 13;
const uint OCCUPIED_MIDDLE_LED_PIN = 14;
const uint OCCUPIED_LOWER_LED_PIN = 15;

const uint REED_1_PIN = 19;
const uint REED_2_PIN = 18;
const uint REED_3_PIN = 17;
const uint REED_4_PIN = 16;

void init_sign();

void show_three_bit_binary(int number, uint upper, uint middle, uint lower);

int main() {
    gpio_init(ONBOARD_LED_PIN);
    gpio_init(ERROR_UPPER_LED_PIN);
    gpio_init(ERROR_MIDDLE_LED_PIN);
    gpio_init(ERROR_LOWER_LED_PIN);
    gpio_init(OCCUPIED_UPPER_LED_PIN);
    gpio_init(OCCUPIED_MIDDLE_LED_PIN);
    gpio_init(OCCUPIED_LOWER_LED_PIN);
    gpio_init(REED_1_PIN);
    gpio_init(REED_2_PIN);
    gpio_init(REED_3_PIN);
    gpio_init(REED_4_PIN);

    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_MIDDLE_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_LOWER_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_MIDDLE_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_LOWER_LED_PIN, GPIO_OUT);
    gpio_set_dir(REED_1_PIN, GPIO_IN);
    gpio_set_dir(REED_2_PIN, GPIO_IN);
    gpio_set_dir(REED_3_PIN, GPIO_IN);
    gpio_set_dir(REED_4_PIN, GPIO_IN);

    rail_contact_point_t *p1 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p2 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p3 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p4 = malloc(sizeof(rail_contact_point_t));

    rail_contact_point_init(p1, 1);
    rail_contact_point_init(p2, 2);
    rail_contact_point_init(p3, 3);
    rail_contact_point_init(p4, 4);

    rail_contact_point_directed_t *d1 = malloc(sizeof(rail_contact_point_directed_t));
    rail_contact_point_directed_t *d2 = malloc(sizeof(rail_contact_point_directed_t));

    rail_contact_point_directed_init(d1, 1, p1, p2);
    rail_contact_point_directed_init(d2, 2, p4, p3);

    rail_contact_counter_t *c = malloc(sizeof(rail_contact_counter_t));
    rail_contact_counter_init(c, 1);

    rail_contact_counter_add_contact_point_directed(c, d1);
    rail_contact_counter_add_contact_point_directed(c, d2);

    rail_vacancy_t *v = malloc(sizeof(rail_vacancy_t));
    rail_vacancy_init(v);
    rail_vacancy_add_contact_counter(v, c);

    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    bool reed1_was_high = false;
    bool reed2_was_high = false;
    bool reed3_was_high = false;
    bool reed4_was_high = false;

    gpio_put(ONBOARD_LED_PIN, true);
    sleep_ms(1000);
    gpio_put(ONBOARD_LED_PIN, false);

    while (true) {
        bool reed1 = gpio_get(REED_1_PIN);
        bool reed2 = gpio_get(REED_2_PIN);
        bool reed3 = gpio_get(REED_3_PIN);
        bool reed4 = gpio_get(REED_4_PIN);

        if (reed1 && !reed1_was_high) {
            reed1_was_high = true;
            rail_vacancy_trigger(v, p1, error);
        }

        if (reed2 && !reed2_was_high) {
            reed2_was_high = true;
            rail_vacancy_trigger(v, p2, error);
        }

        if (reed3 && !reed3_was_high) {
            reed3_was_high = true;
            rail_vacancy_trigger(v, p3, error);
        }

        if (reed4 && !reed4_was_high) {
            reed4_was_high = true;
            rail_vacancy_trigger(v, p4, error);
        }

        if (!reed1 && reed1_was_high) {
            reed1_was_high = false;
        }

        if (!reed2 && reed2_was_high) {
            reed2_was_high = false;
        }

        if (!reed3 && reed3_was_high) {
            reed3_was_high = false;
        }

        if (!reed4 && reed4_was_high) {
            reed4_was_high = false;
        }

        if (error_has_error(error)) {
            show_three_bit_binary(error->codes[0], ERROR_UPPER_LED_PIN, ERROR_MIDDLE_LED_PIN, ERROR_LOWER_LED_PIN);
        } else {
            gpio_put(ERROR_UPPER_LED_PIN, false);
            gpio_put(ERROR_MIDDLE_LED_PIN, false);
            gpio_put(ERROR_LOWER_LED_PIN, false);
        }

        show_three_bit_binary(c->count, OCCUPIED_UPPER_LED_PIN, OCCUPIED_MIDDLE_LED_PIN, OCCUPIED_LOWER_LED_PIN);

        sleep_ms(10);
    }
}

void show_three_bit_binary(int number, uint upper, uint middle, uint lower) {
    if (number == 0) {
        gpio_put(upper, false);
        gpio_put(middle, false);
        gpio_put(lower, false);
    } else if (number == 1) {
        gpio_put(upper, false);
        gpio_put(middle, false);
        gpio_put(lower, true);
    } else if (number == 2) {
        gpio_put(upper, false);
        gpio_put(middle, true);
        gpio_put(lower, false);
    } else if (number == 3) {
        gpio_put(upper, false);
        gpio_put(middle, true);
        gpio_put(lower, true);
    } else if (number == 4) {
        gpio_put(upper, true);
        gpio_put(middle, false);
        gpio_put(lower, false);
    } else if (number == 5) {
        gpio_put(upper, true);
        gpio_put(middle, false);
        gpio_put(lower, true);
    } else if (number == 6) {
        gpio_put(upper, true);
        gpio_put(middle, true);
        gpio_put(lower, false);
    } else if (number >= 7) {
        gpio_put(upper, true);
        gpio_put(middle, true);
        gpio_put(lower, true);
    }
}
