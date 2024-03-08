#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include <stdbool.h>
#include <stdlib.h>

#include "RP2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "rail/vacancy.h"

#define REED_1_PIN 19
#define REED_2_PIN 18
#define REED_3_PIN 17
#define REED_4_PIN 16

int main() {
    stdio_init_all();

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

    uint32_t count_c = 0;

    printf("Initialized vacancy detection. Continue in 5s ...\n");
    sleep_ms(5000);
    printf("Waiting for action\n");

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
            error_print(error);
        }

        if (count_c != c->count) {
            printf("Count: %d\n", c->count);
        }

        count_c = c->count;

        sleep_ms(100);
    }
}
