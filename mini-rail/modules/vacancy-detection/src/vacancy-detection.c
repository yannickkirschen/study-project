#include <stdlib.h>

#include "error.h"
#include "rail/vacancy.h"

void rail_vacancy_init(rail_vacancy_t *vacancy) {
    vacancy->contact_counters = NULL;
    vacancy->number_contact_counters = 0;
}

void rail_vacancy_add_contact_counter(rail_vacancy_t *vacancy, rail_contact_counter_t *counter) {
    rail_contact_counter_t **new = malloc(sizeof(rail_contact_counter_t *) * (vacancy->number_contact_counters + 1));
    for (int i = 0; i < vacancy->number_contact_counters; i++) {
        new[i] = vacancy->contact_counters[i];
    }
    new[vacancy->number_contact_counters] = counter;

    free(vacancy->contact_counters);
    vacancy->contact_counters = new;
    vacancy->number_contact_counters++;
}

void rail_contact_counter_reset(rail_contact_counter_t *counter) {
    free(counter->directions_to);

    counter->count = 0;
    counter->directions_to = NULL;
    counter->number_directions_to = 0;

    for (int i = 0; i < counter->number_contact_points_directed; i++) {
        rail_contact_point_directed_t *point = counter->contact_points_directed[i];
        point->is_entering = false;
        point->is_leaving = false;
    }
}

void rail_vacancy_trigger(rail_vacancy_t *vacancy, rail_contact_point_t *raw_point, error_t *error) {
    rail_contact_trigger_t *trigger = malloc(sizeof(rail_contact_trigger_t));
    rail_vacancy_find_contact_counter(vacancy, raw_point, trigger);

    rail_contact_counter_t *counter = trigger->contact_counter;
    rail_contact_point_directed_t *point = trigger->contact_point_directed;

    if (counter == NULL || point == NULL) {
        error_add(error, 1, "Contact counter not found");
        return;
    }

    bool is_inner = point->inner == raw_point;
    bool is_outer = point->outer == raw_point;

    if (point->is_entering && is_inner) {
        point->is_entering = false;
        counter->count++;
    } else if (point->is_leaving && is_outer) {
        point->is_leaving = false;
        counter->count--;

        if (counter->count == 0) {
            free(counter->directions_to);
            counter->directions_to = NULL;
            counter->number_directions_to = 0;
        }
    } else if (!point->is_entering && !point->is_leaving) {
        if (is_inner) {
            if (counter->number_directions_to > 1) {
                bool found = false;
                for (int i = 0; i < counter->number_directions_to; i++) {
                    if (counter->directions_to[i] == point) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    error_add(error, 6, "Logic error");
                    return;
                }

                free(counter->directions_to);
                counter->directions_to = malloc(sizeof(rail_contact_point_directed_t));
                counter->directions_to[0] = point;
                counter->number_directions_to = 1;

                point->is_leaving = true;
            } else if (counter->number_directions_to == 1) {
                if (counter->directions_to[0] == point) {
                    point->is_leaving = true;
                } else {
                    error_add(error, 4, "Eschede error");
                    return;
                }
            } else {
                error_add(error, 5, "Logic error");
                return;
            }
        } else if (is_outer) {
            point->is_entering = true;

            bool found = false;
            for (int i = 0; i < counter->number_directions_to; i++) {
                if (counter->directions_to[i] == point) {
                    found = true;
                    break;
                }
            }

            if (found) {
                error_add(error, 3, "Section is blocked by another train");
                return;
            }

            // Find the direction(s) the train is going to
            counter->directions_to = malloc(sizeof(rail_contact_point_directed_t) * counter->number_contact_points_directed - 1);
            counter->number_directions_to = counter->number_contact_points_directed - 1;

            int j = 0;
            for (int i = 0; i < counter->number_contact_points_directed; i++) {
                if (counter->contact_points_directed[i] != point) {
                    counter->directions_to[j] = counter->contact_points_directed[i];
                    j++;
                }
            }
        }
    } else {
        error_add(error, 2, "Invalid contact point");
        return;
    }
}

void rail_vacancy_find_contact_counter(rail_vacancy_t *vacancy, rail_contact_point_t *contact,
                                       rail_contact_trigger_t *trigger) {
    for (int i = 0; i < vacancy->number_contact_counters; i++) {
        rail_contact_counter_t *current_counter = vacancy->contact_counters[i];
        for (int j = 0; j < current_counter->number_contact_points_directed; j++) {
            rail_contact_point_directed_t *current_directed = current_counter->contact_points_directed[j];
            if (current_directed->outer == contact || current_directed->inner == contact) {
                trigger->contact_counter = current_counter;
                trigger->contact_point_directed = current_directed;
                return;
            }
        }
    }
}
