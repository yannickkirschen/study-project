#include "assert.h"

#include <stdlib.h>

#include "error.h"

void assert(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points) {
    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    for (int i = 0; i < number_points; i++) {
        rail_vacancy_trigger(v, points[i], error);
        error_print(error);
    }

    free(error);
}

void assertError(rail_vacancy_t *v, rail_contact_point_t *points[], int number_points, int error_code) {
    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    for (int i = 0; i < number_points; i++) {
        rail_vacancy_trigger(v, points[i], error);
        error_print(error);
    }

    free(error);
}

void assertWithChange(rail_vacancy_t *v, rail_contact_counter_t *counter, rail_contact_point_t *points_before[], int number_points_before, rail_contact_point_t *points_after[], int number_points_after) {
    assert(v, points_before, number_points_before);

    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    rail_contact_counter_change_direction(counter, error);
    error_print(error);

    assert(v, points_after, number_points_after);

    free(error);
}
