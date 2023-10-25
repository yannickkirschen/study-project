#include "assert.h"

#include <stdlib.h>

void assert(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points) {
    rail_error_t *error = malloc(sizeof(rail_error_t));
    rail_error_init(error);

    for (int i = 0; i < number_points; i++) {
        rail_vacancy_trigger(v, points[i], error);
        if (rail_error_has_error(error)) {
            printf("Error: %i, %s\n", error->code, error->message);
        }
    }

    free(error);
}

void assertError(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points, int error_code) {
    rail_error_t *error = malloc(sizeof(rail_error_t));
    rail_error_init(error);

    for (int i = 0; i < number_points; i++) {
        rail_vacancy_trigger(v, points[i], error);
        if (rail_error_has_error(error) && error->code != error_code) {
            printf("Error: %i, %s\n", error->code, error->message);
        }
    }

    free(error);
}

void assertWithChange(rail_vacancy_t *v, rail_contact_counter_t *counter, rail_contact_point_t *points_before[], int number_points_before, rail_contact_point_t *points_after[], int number_points_after) {
    assert(v, points_before, number_points_before);

    rail_error_t *error = malloc(sizeof(rail_error_t));
    rail_error_init(error);

    rail_contact_counter_change_direction(counter, error);
    if (rail_error_has_error(error)) {
        printf("Error: %i, %s\n", error->code, error->message);
    }

    assert(v, points_after, number_points_after);

    free(error);
}
