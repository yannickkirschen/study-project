#include <stdbool.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "rail/vacancy.h"

const uint ONBOARD_LED_PIN = 25;
const uint ERROR_UPPER_LED_PIN = 7;
const uint ERROR_MIDDLE_LED_PIN = 8;
const uint ERROR_LOWER_LED_PIN = 9;
const uint OCCUPIED_UPPER_LED_PIN = 10;
const uint OCCUPIED_MIDDLE_LED_PIN = 11;
const uint OCCUPIED_LOWER_LED_PIN = 12;
const uint CONTACT_1_LED_PIN = 22;
const uint CONTACT_2_LED_PIN = 21;
const uint CONTACT_3_LED_PIN = 2;
const uint CONTACT_4_LED_PIN = 3;
const uint COUNTER_UPPER_LED_PIN = 4;
const uint COUNTER_MIDDLE_LED_PIN = 5;
const uint COUNTER_LOWER_LED_PIN = 6;
const uint REED_1_PIN = 13;
const uint REED_2_PIN = 14;
const uint REED_3_PIN = 15;
const uint REED_4_PIN = 16;

void init_sign();

void callback(uint gpio, uint32_t event);

rail_vacancy_t *init_detection();

void show_three_bit_binary(int number, uint upper, uint middle, uint lower);

rail_vacancy_t *vacancy;
rail_contact_counter_t *counter;
rail_contact_point_t *point1;
rail_contact_point_t *point2;
rail_contact_point_t *point3;
rail_contact_point_t *point4;

int debug_counter = 0;

int main() {
    printf("hello, world\n");
    vacancy = init_detection();

    gpio_init(ONBOARD_LED_PIN);
    gpio_init(ERROR_UPPER_LED_PIN);
    gpio_init(ERROR_MIDDLE_LED_PIN);
    gpio_init(ERROR_LOWER_LED_PIN);
    gpio_init(OCCUPIED_UPPER_LED_PIN);
    gpio_init(OCCUPIED_MIDDLE_LED_PIN);
    gpio_init(OCCUPIED_LOWER_LED_PIN);
    gpio_init(CONTACT_1_LED_PIN);
    gpio_init(CONTACT_2_LED_PIN);
    gpio_init(CONTACT_3_LED_PIN);
    gpio_init(CONTACT_4_LED_PIN);
    gpio_init(COUNTER_UPPER_LED_PIN);
    gpio_init(COUNTER_MIDDLE_LED_PIN);
    gpio_init(COUNTER_LOWER_LED_PIN);
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
    gpio_set_dir(CONTACT_1_LED_PIN, GPIO_OUT);
    gpio_set_dir(CONTACT_2_LED_PIN, GPIO_OUT);
    gpio_set_dir(CONTACT_3_LED_PIN, GPIO_OUT);
    gpio_set_dir(CONTACT_4_LED_PIN, GPIO_OUT);
    gpio_set_dir(COUNTER_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(COUNTER_MIDDLE_LED_PIN, GPIO_OUT);
    gpio_set_dir(COUNTER_LOWER_LED_PIN, GPIO_OUT);
    gpio_set_dir(REED_1_PIN, GPIO_IN);
    gpio_set_dir(REED_2_PIN, GPIO_IN);
    gpio_set_dir(REED_3_PIN, GPIO_IN);
    gpio_set_dir(REED_4_PIN, GPIO_IN);

    gpio_set_irq_enabled_with_callback(REED_1_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_2_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_3_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_4_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);

    init_sign();
    while (true) {
    }
}

void callback(uint gpio, uint32_t event_mask) {
    rail_error_t *error = malloc(sizeof(rail_error_t));
    rail_error_init(error);

    if (event_mask == GPIO_IRQ_EDGE_RISE) {
        printf("Rise on switch %i\n", gpio);
        gpio_put(ONBOARD_LED_PIN, true);

        debug_counter++;
        show_three_bit_binary(debug_counter, COUNTER_UPPER_LED_PIN, COUNTER_MIDDLE_LED_PIN, COUNTER_LOWER_LED_PIN);

        switch (gpio) {
        case REED_1_PIN:
            rail_vacancy_trigger(vacancy, point1, error);
            gpio_put(CONTACT_1_LED_PIN, true);
            break;
        case REED_2_PIN:
            rail_vacancy_trigger(vacancy, point2, error);
            gpio_put(CONTACT_2_LED_PIN, true);
            break;
        case REED_3_PIN:
            rail_vacancy_trigger(vacancy, point3, error);
            gpio_put(CONTACT_3_LED_PIN, true);
            break;
        case REED_4_PIN:
            rail_vacancy_trigger(vacancy, point4, error);
            gpio_put(CONTACT_4_LED_PIN, true);
            break;
        default:
            rail_error_add(error, 3, "Unknown GPIO pin triggered");
            break;
        }
    } else {
        gpio_put(ONBOARD_LED_PIN, false);
        gpio_put(CONTACT_1_LED_PIN, false);
        gpio_put(CONTACT_2_LED_PIN, false);
        gpio_put(CONTACT_3_LED_PIN, false);
        gpio_put(CONTACT_4_LED_PIN, false);
    }

    if (rail_error_has_error(error)) {
        show_three_bit_binary(error->code, ERROR_UPPER_LED_PIN, ERROR_MIDDLE_LED_PIN, ERROR_LOWER_LED_PIN);
        free(error);
    } else {
        gpio_put(ERROR_UPPER_LED_PIN, false);
        gpio_put(ERROR_MIDDLE_LED_PIN, false);
        gpio_put(ERROR_LOWER_LED_PIN, false);
    }

    show_three_bit_binary(counter->count, OCCUPIED_UPPER_LED_PIN, OCCUPIED_MIDDLE_LED_PIN, OCCUPIED_LOWER_LED_PIN);
}

rail_vacancy_t *init_detection() {
    rail_contact_point_t *p1 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p2 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p3 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p4 = malloc(sizeof(rail_contact_point_t));

    p1->id = 1;
    p2->id = 2;
    p3->id = 3;
    p4->id = 4;

    rail_contact_point_directed_t *d1 = malloc(sizeof(rail_contact_point_directed_t));
    rail_contact_point_directed_t *d2 = malloc(sizeof(rail_contact_point_directed_t));

    d1->outer = p1;
    d1->inner = p2;

    d2->inner = p3;
    d2->outer = p4;

    rail_contact_counter_t *c = malloc(sizeof(rail_contact_counter_t));
    c->contact_points_directed = malloc(sizeof(rail_contact_point_directed_t) * 2);

    c->contact_points_directed[0] = d1;
    c->contact_points_directed[1] = d2;

    c->number_contact_points_directed = 2;

    c->count = 0;

    rail_vacancy_t *v = malloc(sizeof(rail_vacancy_t));
    v->contact_counters = malloc(sizeof(rail_contact_counter_t));
    v->contact_counters[0] = c;
    v->number_contact_counters = 1;

    counter = c;
    point1 = p1;
    point2 = p2;
    point3 = p3;
    point4 = p4;

    return v;
}

void init_sign() {
    gpio_put(ONBOARD_LED_PIN, true);
    sleep_ms(200);
    gpio_put(ONBOARD_LED_PIN, false);

    gpio_put(CONTACT_1_LED_PIN, true);
    sleep_ms(200);
    gpio_put(CONTACT_1_LED_PIN, false);

    gpio_put(CONTACT_2_LED_PIN, true);
    sleep_ms(200);
    gpio_put(CONTACT_2_LED_PIN, false);

    gpio_put(CONTACT_3_LED_PIN, true);
    sleep_ms(200);
    gpio_put(CONTACT_3_LED_PIN, false);

    gpio_put(CONTACT_4_LED_PIN, true);
    sleep_ms(200);
    gpio_put(CONTACT_4_LED_PIN, false);

    gpio_put(COUNTER_UPPER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(COUNTER_UPPER_LED_PIN, false);

    gpio_put(COUNTER_MIDDLE_LED_PIN, true);
    sleep_ms(200);
    gpio_put(COUNTER_MIDDLE_LED_PIN, false);

    gpio_put(COUNTER_LOWER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(COUNTER_LOWER_LED_PIN, false);

    gpio_put(ERROR_UPPER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(ERROR_UPPER_LED_PIN, false);

    gpio_put(ERROR_MIDDLE_LED_PIN, true);
    sleep_ms(200);
    gpio_put(ERROR_MIDDLE_LED_PIN, false);

    gpio_put(ERROR_LOWER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(ERROR_LOWER_LED_PIN, false);

    gpio_put(OCCUPIED_UPPER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(OCCUPIED_UPPER_LED_PIN, false);

    gpio_put(OCCUPIED_MIDDLE_LED_PIN, true);
    sleep_ms(200);
    gpio_put(OCCUPIED_MIDDLE_LED_PIN, false);

    gpio_put(OCCUPIED_LOWER_LED_PIN, true);
    sleep_ms(200);
    gpio_put(OCCUPIED_LOWER_LED_PIN, false);

    for (int i = 0; i < 8; i++) {
        show_three_bit_binary(i, COUNTER_UPPER_LED_PIN, COUNTER_MIDDLE_LED_PIN, COUNTER_LOWER_LED_PIN);
        sleep_ms(200);
    }
    show_three_bit_binary(0, COUNTER_UPPER_LED_PIN, COUNTER_MIDDLE_LED_PIN, COUNTER_LOWER_LED_PIN);

    for (int i = 0; i < 8; i++) {
        show_three_bit_binary(i, ERROR_UPPER_LED_PIN, ERROR_MIDDLE_LED_PIN, ERROR_LOWER_LED_PIN);
        sleep_ms(200);
    }
    show_three_bit_binary(0, ERROR_UPPER_LED_PIN, ERROR_MIDDLE_LED_PIN, ERROR_LOWER_LED_PIN);

    for (int i = 0; i < 8; i++) {
        show_three_bit_binary(i, OCCUPIED_UPPER_LED_PIN, OCCUPIED_MIDDLE_LED_PIN, OCCUPIED_LOWER_LED_PIN);
        sleep_ms(200);
    }
    show_three_bit_binary(0, OCCUPIED_UPPER_LED_PIN, OCCUPIED_MIDDLE_LED_PIN, OCCUPIED_LOWER_LED_PIN);
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
