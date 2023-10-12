#ifndef RAIL_VACANCY_H
#define RAIL_VACANCY_H

#include <stdbool.h>
#include <stdio.h>

#include "rail/error.h"

/*
    A contact point is a point on the rail where a train can be detected. It may
    be of any kind of sensor, e.g. a light barrier, a pressure sensor, Reed
    contact, Hall sensor, etc.

    When a contact point is triggered, it is not known whether a train is
    entering or leaving the section. Therefore, a directed contact point can be
    used.
*/
struct rail_contact_point {
    int id;
} typedef rail_contact_point;

/*
    A directed contact point is made up of two contact points. The outer contact
    point is the contact point that is triggered first when a train is entering
    a section. The inner contact point is the contact point that is triggered
    first when a train is leaving a section.
*/
struct rail_contact_point_directed {
    rail_contact_point *outer;
    rail_contact_point *inner;

    bool is_entering;
    bool is_leaving;
} typedef rail_contact_point_directed;

struct rail_contact_counter {
    rail_contact_point_directed **contact_points_directed;
    int number_contact_points_directed;

    int count;
} typedef rail_contact_counter;

struct rail_contact_trigger {
    rail_contact_counter *contact_counter;
    rail_contact_point_directed *contact_point_directed;
} typedef rail_contact_trigger;

struct rail_vacancy {
    rail_contact_counter **contact_counters;
    int number_contact_counters;
} typedef rail_vacancy;

void rail_vacancy_trigger(rail_vacancy *vacancy, rail_contact_point *contact_point, rail_error *error);

void rail_vacancy_find_contact_counter(rail_vacancy *vacancy_detection, rail_contact_point *contact_point, rail_contact_trigger *trigger);

#endif  // RAIL_VACANCY_H
