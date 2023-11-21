#ifndef MINI_RAIL_INTERLOCKING_H
#define MINI_RAIL_INTERLOCKING_H

#include "error.h"
#include "graph.h"

#define ERROR_INTERLOCKING_ROUTE_TOO_SHORT 1
#define ERROR_INTERLOCKING_ROUTE_START_NOT_SIGNAL 2
#define ERROR_INTERLOCKING_ROUTE_END_NOT_SIGNAL_OR_OPEN_TRACK 3
#define ERROR_INTERLOCKING_ROUTE_CONTAINS_LOCKED_ELEMENT 4

typedef enum {
    RAIL_SIGNAL_INDICATION_STOP,
    RAIL_SIGNAL_INDICATION_CLEAR
} mini_rail_signal_indication_t;

char *rail_signal_indication_string(mini_rail_signal_indication_t indication);

typedef struct {
    int id;
    char *display_name;
    mini_rail_signal_indication_t indication;
} mini_rail_signal_t;

void rail_signal_init(mini_rail_signal_t *signal, int id);
char *rail_signal_string(mini_rail_signal_t *signal);
void rail_signal_print(mini_rail_signal_t *signal);
void rail_signal_set_indication(mini_rail_signal_t *signal, mini_rail_signal_indication_t indication);
void rail_signal_set_stop(mini_rail_signal_t *signal);

typedef struct {
    int id;
    char *display_name;
} mini_rail_open_track_t;

void rail_open_track_init(mini_rail_open_track_t *open_track, int id);
char *rail_open_track_string(mini_rail_open_track_t *open_track);
void rail_open_track_print(mini_rail_open_track_t *open_track);

typedef enum {
    RAIL_SWITCH_POSITION_LEFT,
    RAIL_SWITCH_POSITION_RIGHT
} mini_rail_switch_position_t;

char *rail_switch_position_string(mini_rail_switch_position_t position);

typedef struct {
    int id;
    char *display_name;
    mini_rail_switch_position_t position;
    mini_rail_switch_position_t base_position;

    int left_id;
    int right_id;
} mini_rail_switch_t;

void rail_switch_init(mini_rail_switch_t *switch_, int id, mini_rail_switch_position_t base_position, int left_id, int right_id);
char *rail_switch_string(mini_rail_switch_t *switch_);
void rail_switch_print(mini_rail_switch_t *switch_);
void rail_switch_set_position(mini_rail_switch_t *switch_, mini_rail_switch_position_t position);
void rail_switch_to_base_position(mini_rail_switch_t *switch_);

typedef enum {
    RAIL_ELEMENT_SIGNAL,
    RAIL_ELEMENT_SWITCH,
    RAIL_ELEMENT_OPEN_TRACK,
    RAIL_ELEMENT_NONE
} mini_rail_element_type_t;

mini_rail_element_type_t rail_element_type_from_string(char *string);
char *rail_element_type_string(mini_rail_element_type_t type);

typedef struct {
    int id;
    bool locked;

    mini_rail_element_type_t type;
    union {
        mini_rail_signal_t *signal;
        mini_rail_switch_t *_switch;
        mini_rail_open_track_t *open_track;
    } spec;

    mini_rail_element_type_t points_to_type;
    union {
        mini_rail_signal_t *signal;
        mini_rail_switch_t *_switch;
        mini_rail_open_track_t *open_track;
    } points_to_spec;
} mini_rail_element_t;

void rail_element_init(mini_rail_element_t *element, int id, mini_rail_element_type_t type);
void rail_element_print(mini_rail_element_t *element);
void rail_elements_print(mini_rail_element_t *elements);

typedef struct {
    int key;
    mini_rail_element_t *value;
} mini_rail_element_map_t;

typedef struct {
    mini_rail_element_map_t *elements;
    graph_t *graph;
} mini_rail_interlocking_t;

void rail_interlocking_init(mini_rail_interlocking_t *interlocking);
void rail_interlocking_element_add(mini_rail_interlocking_t *interlocking, int id, mini_rail_element_t *element);
int rail_interlocking_element_find(mini_rail_interlocking_t *interlocking, char *name);
mini_rail_element_t *rail_interlocking_route_translate(mini_rail_interlocking_t *interlocking, int *path);
mini_rail_element_t *rail_interlocking_route_find_and_set(mini_rail_interlocking_t *interlocking, int start_id, int end_id, error_t *error);

void rail_interlocking_routes_clean(mini_rail_element_t **routes);
mini_rail_element_t *rail_interlocking_route_choose_best(mini_rail_element_t **routes);
void rail_interlocking_route_set(mini_rail_element_t *route, error_t *error);

#endif  // MINI_RAIL_INTERLOCKING_H
