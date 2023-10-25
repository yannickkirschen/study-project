#include <stdbool.h>

#include "rail/vacancy.h"

void rail_contact_point_init(rail_contact_point_t *point, int id) {
    point->id = id;
}

void rail_contact_point_directed_init(rail_contact_point_directed_t *point, int id, rail_contact_point_t *outer,
                                      rail_contact_point_t *inner) {
    point->id = id;
    point->outer = outer;
    point->inner = inner;
    point->is_entering = false;
    point->is_leaving = false;
}
