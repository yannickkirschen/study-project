#ifndef MINI_RAIL_VACANCY_H
#define MINI_RAIL_VACANCY_H

#include <stdbool.h>
#include <stdio.h>

#include "error.h"

typedef struct {
    int id;
} rail_contact_point_t;

void rail_contact_point_init(rail_contact_point_t *point, int id);

typedef struct {
    int id;

    rail_contact_point_t *outer;
    rail_contact_point_t *inner;

    bool is_entering;
    bool is_leaving;
} rail_contact_point_directed_t;

void rail_contact_point_directed_init(rail_contact_point_directed_t *point, int id, rail_contact_point_t *outer,
                                      rail_contact_point_t *inner);

typedef struct {
    int id;
    int count;

    rail_contact_point_directed_t **contact_points_directed;
    int number_contact_points_directed;

    rail_contact_point_directed_t **directions_to;
    int number_directions_to;
} rail_contact_counter_t;

void rail_contact_counter_init(rail_contact_counter_t *counter, int id);
void rail_contact_counter_reset(rail_contact_counter_t *counter);
void rail_contact_counter_add_contact_point_directed(rail_contact_counter_t *counter,
                                                     rail_contact_point_directed_t *point);
void rail_contact_counter_change_direction(rail_contact_counter_t *counter, error_t *error);

typedef struct {
    rail_contact_counter_t *contact_counter;
    rail_contact_point_directed_t *contact_point_directed;
} rail_contact_trigger_t;

typedef struct {
    rail_contact_counter_t **contact_counters;
    int number_contact_counters;
} rail_vacancy_t;

void rail_vacancy_init(rail_vacancy_t *vacancy);
void rail_vacancy_add_contact_counter(rail_vacancy_t *vacancy, rail_contact_counter_t *counter);
void rail_vacancy_trigger(rail_vacancy_t *vacancy, rail_contact_point_t *raw_point, error_t *error);
void rail_vacancy_find_contact_counter(rail_vacancy_t *vacancy, rail_contact_point_t *contact_point,
                                       rail_contact_trigger_t *trigger);

#endif  // MINI_RAIL_VACANCY_H
