#include <stdlib.h>

#include "rail/error.h"
#include "rail/vacancy.h"

void rail_vacancy_trigger(rail_vacancy *vacancy, rail_contact_point *point, rail_error *error) {
    rail_contact_trigger *trigger = malloc(sizeof(rail_contact_trigger));
    rail_vacancy_find_contact_counter(vacancy, point, trigger);

    rail_contact_counter *counter = trigger->contact_counter;
    rail_contact_point_directed *directed = trigger->contact_point_directed;

    if (counter == NULL || directed == NULL) {
        rail_error_add(error, "Contact counter not found");
        return;
    }

    bool is_inner = directed->inner == point;
    bool is_outer = directed->outer == point;

    if (directed->is_entering && is_inner) {
        directed->is_entering = false;
        counter->count++;
    } else if (directed->is_leaving && is_outer) {
        directed->is_leaving = false;
        counter->count--;
    } else if (!directed->is_entering && !directed->is_leaving) {
        if (is_inner) {
            directed->is_leaving = true;
        } else if (is_outer) {
            directed->is_entering = true;
        }
    } else {
        rail_error_add(error, "Invalid contact point");
        return;
    }
}

void rail_vacancy_find_contact_counter(rail_vacancy *vacancy, rail_contact_point *contact, rail_contact_trigger *trigger) {
    for (int i = 0; i < vacancy->number_contact_counters; i++) {
        rail_contact_counter *current_counter = vacancy->contact_counters[i];
        for (int j = 0; j < current_counter->number_contact_points_directed; j++) {
            rail_contact_point_directed *current_directed = current_counter->contact_points_directed[j];
            if (current_directed->outer == contact || current_directed->inner == contact) {
                trigger->contact_counter = current_counter;
                trigger->contact_point_directed = current_directed;
                return;
            }
        }
    }
}
