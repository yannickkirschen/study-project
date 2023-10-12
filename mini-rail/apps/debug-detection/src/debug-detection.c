#include <stdlib.h>

#include "rail/error.h"
#include "rail/vacancy.h"

int main() {
    rail_contact_point *p1 = malloc(sizeof(rail_contact_point));
    rail_contact_point *p2 = malloc(sizeof(rail_contact_point));
    rail_contact_point *p3 = malloc(sizeof(rail_contact_point));
    rail_contact_point *p4 = malloc(sizeof(rail_contact_point));

    p1->id = 1;
    p2->id = 2;
    p3->id = 3;
    p4->id = 4;

    rail_contact_point_directed *d1 = malloc(sizeof(rail_contact_point_directed));
    rail_contact_point_directed *d2 = malloc(sizeof(rail_contact_point_directed));

    d1->outer = p1;
    d1->inner = p2;

    d2->inner = p3;
    d2->outer = p4;

    rail_contact_counter *c = malloc(sizeof(rail_contact_counter));
    c->contact_points_directed = malloc(sizeof(rail_contact_point_directed) * 2);

    c->contact_points_directed[0] = d1;
    c->contact_points_directed[1] = d2;

    c->number_contact_points_directed = 2;

    c->count = 0;

    rail_vacancy *v = malloc(sizeof(rail_vacancy));
    v->contact_counters = malloc(sizeof(rail_contact_counter));
    v->contact_counters[0] = c;
    v->number_contact_counters = 1;

    rail_error *error = malloc(sizeof(rail_error));
    rail_error_init(error);

    rail_vacancy_trigger(v, p1, error);
    rail_vacancy_trigger(v, p2, error);

    printf("Axle 1 is in the section. Count is: %i\n", c->count);

    rail_vacancy_trigger(v, p1, error);
    rail_vacancy_trigger(v, p2, error);

    printf("Axle 2 is in the section. Count is: %i\n", c->count);

    rail_vacancy_trigger(v, p3, error);
    rail_vacancy_trigger(v, p4, error);

    printf("Axle 1 is out of the section. Count is: %i\n", c->count);

    rail_vacancy_trigger(v, p3, error);
    rail_vacancy_trigger(v, p4, error);

    printf("Axle 2 is out of the section. Count is: %i\n", c->count);

    if (error->number_messages != 0) {
        printf("Error: %s\n", error->messages[0]);
    }

    return 0;
}
