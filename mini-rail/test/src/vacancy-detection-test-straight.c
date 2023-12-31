#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define RAIL_TEST_ASSERT_IMPLEMENTATION

#include <stdlib.h>

#include "assert.h"
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

    printf("Test normal route\n");
    rail_vacancy_assert(v, (rail_contact_point_t *[]){p1, p2, p3, p4}, 4);
    rail_contact_counter_reset(c);

    printf("Test reverse route\n");
    rail_vacancy_assert(v, (rail_contact_point_t *[]){p4, p3, p2, p1}, 4);
    rail_contact_counter_reset(c);

    printf("Test change in direction (results in error)\n");
    rail_vacancy_assert_error(v, (rail_contact_point_t *[]){p1, p2, p2, p1}, 4, 4);
    rail_contact_counter_reset(c);

    printf("Test drive with no entry\n");
    rail_vacancy_assert_error(v, (rail_contact_point_t *[]){p2, p1}, 2, 5);
    rail_contact_counter_reset(c);

    printf("Test drive with double inner trigger\n");
    rail_vacancy_assert(v, (rail_contact_point_t *[]){p1, p2, p1, p3, p2, p4, p3, p4}, 8);
    rail_contact_counter_reset(c);

    printf("Test change in direction with change before\n");
    rail_vacancy_assert_with_change(v, c, (rail_contact_point_t *[]){p1, p2, p1, p2}, 4, (rail_contact_point_t *[]){p2, p1, p2, p1}, 4);
    return 0;
}
