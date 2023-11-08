#include <stdlib.h>

#include "rail/vacancy.h"

void rail_contact_counter_init(rail_contact_counter_t *counter, int id) {
    counter->id = id;
    counter->count = 0;

    counter->contact_points_directed = NULL;
    counter->number_contact_points_directed = 0;

    counter->directions_to = NULL;
    counter->number_directions_to = 0;
}

void rail_contact_counter_add_contact_point_directed(rail_contact_counter_t *counter,
                                                     rail_contact_point_directed_t *point) {
    if (counter->number_contact_points_directed == 0) {
        counter->contact_points_directed = malloc(sizeof(rail_contact_point_directed_t *));
        counter->contact_points_directed[0] = point;
        counter->number_contact_points_directed++;
    } else {
        rail_contact_point_directed_t **new = malloc(sizeof(rail_contact_point_directed_t) * (counter->number_contact_points_directed + 1));
        for (int i = 0; i < counter->number_contact_points_directed; i++) {
            new[i] = counter->contact_points_directed[i];
        }
        new[counter->number_contact_points_directed] = point;

        free(counter->contact_points_directed);
        counter->contact_points_directed = new;
        counter->number_contact_points_directed++;
    }
}

void rail_contact_counter_change_direction(rail_contact_counter_t *counter, error_t *error) {
    if (counter->count == 0) {
        error_add(error, 7, "No train in section");
        return;
    }

    if (counter->number_directions_to == 0) {
        error_add(error, 8, "No direction to change to");
        return;
    }

    if (counter->number_contact_points_directed > 2) {
        error_add(error, 9, "Multiple directions to change to");
        return;
    }

    rail_contact_point_directed_t *d1 = counter->contact_points_directed[0];
    rail_contact_point_directed_t *d2 = counter->contact_points_directed[1];

    if (counter->directions_to[0] == d1) {
        counter->directions_to[0] = d2;
    } else {
        counter->directions_to[0] = d1;
    }
}
