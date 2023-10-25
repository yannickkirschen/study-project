#include <stdlib.h>

#include "assert.h"
#include "rail/error.h"
#include "rail/vacancy.h"

int main() {
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
    rail_vacancy_add_contact_counter(v, c);

    assert(v, (rail_contact_point_t *[]){p1, p2, p3, p4}, 4);
    rail_contact_counter_reset(c);

    assert(v, (rail_contact_point_t *[]){p4, p3, p2, p1}, 4);
    rail_contact_counter_reset(c);

    assertError(v, (rail_contact_point_t *[]){p1, p2, p2, p1}, 4, 4);
    rail_contact_counter_reset(c);

    assertError(v, (rail_contact_point_t *[]){p2, p1}, 2, 5);
    rail_contact_counter_reset(c);

    assertWithChange(v, c, (rail_contact_point_t *[]){p1, p2, p1, p2}, 4, (rail_contact_point_t *[]){p2, p1, p2, p1}, 4);
    return 0;
}
