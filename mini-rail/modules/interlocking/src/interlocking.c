#include "rail/interlocking.h"

#include <stdio.h>

#include "graph.h"
#include "stb_ds_helper.h"
#include "str.h"

void rail_interlocking_init(mini_rail_interlocking_t *interlocking) {
    interlocking->elements = NULL;
    interlocking->graph = NULL;
}

void rail_interlocking_element_add(mini_rail_interlocking_t *interlocking, int id, mini_rail_element_t *element) {
    hmput(interlocking->elements, id, element);
}

int rail_interlocking_element_find(mini_rail_interlocking_t *interlocking, char *name) {
    for (int i = 0; i < hmlen(interlocking->elements); i++) {
        mini_rail_element_t *element = interlocking->elements[i].value;

        switch (element->type) {
        case RAIL_ELEMENT_SIGNAL:
            if (string_equals(element->spec.signal->display_name, name)) {
                return element->id;
            }
            break;
        case RAIL_ELEMENT_SWITCH: {
            if (string_equals(element->spec._switch->display_name, name)) {
                return element->id;
            }
            break;
        }
        case RAIL_ELEMENT_OPEN_TRACK:
            if (string_equals(element->spec.open_track->display_name, name)) {
                return element->id;
            }
            break;
        case RAIL_ELEMENT_NONE:
            break;
        }
    }

    return -1;
}

mini_rail_element_t *rail_interlocking_route_translate(mini_rail_interlocking_t *interlocking, int *path) {
    mini_rail_element_t *route = NULL;
    for (int i = 0; i < arrlen(path); i++) {
        mini_rail_element_t *element = hmget(interlocking->elements, path[i]);
        arrput(route, *element);
    }

    return route;
}

mini_rail_element_t *rail_interlocking_route_find_and_set(mini_rail_interlocking_t *interlocking, int start_id, int end_id, error_t *error) {
    int **paths = graph_find_paths(interlocking->graph, start_id, end_id);

    mini_rail_element_t **routes = NULL;
    for (int i = 0; i < arrlen(paths); i++) {
        mini_rail_element_t *route = rail_interlocking_route_translate(interlocking, paths[i]);
        arrput(routes, route);
    }

    rail_interlocking_routes_clean(routes);

    mini_rail_element_t *route = rail_interlocking_route_choose_best(routes);
    rail_interlocking_route_set(route, error);
    if (error_has_error(error)) {
        return NULL;
    }

    return route;
}

void rail_interlocking_routes_clean(mini_rail_element_t **routes) {
    for (int i = 0; i < arrlen(routes); i++) {
        mini_rail_element_t *route = routes[i];

        for (int j = 0; j < arrlen(route); j++) {
            mini_rail_element_t *element = &route[j];
            mini_rail_element_t *previous = j > 0 ? &route[j - 1] : NULL;
            mini_rail_element_t *next = j < arrlen(route) - 1 ? &route[j + 1] : NULL;

            if (element->type == RAIL_ELEMENT_SWITCH && previous != NULL && next != NULL) {
                mini_rail_switch_t *sw = element->spec._switch;

                if ((previous->id == sw->left_id && next->id == sw->right_id) ||
                    (previous->id == sw->right_id && next->id == sw->left_id)) {
                    arrdel(routes, i);
                    break;
                }
            }
        }
    }
}

mini_rail_element_t *rail_interlocking_route_choose_best(mini_rail_element_t **routes) {
    if (arrlen(routes) == 0) {
        return NULL;
    }

    return routes[0];
}

void rail_interlocking_route_set(mini_rail_element_t *route, error_t *error) {
    if (arrlen(route) < 2) {
        error_add(error, ERROR_INTERLOCKING_ROUTE_TOO_SHORT, "Route must contain at least 2 elements");
        return;
    }

    mini_rail_element_t *start = &route[0];
    if (start->type != RAIL_ELEMENT_SIGNAL) {
        error_add(error, ERROR_INTERLOCKING_ROUTE_START_NOT_SIGNAL, "Route must start with a signal");
        return;
    }

    mini_rail_element_t *end = &route[arrlen(route) - 1];
    if (end->type != RAIL_ELEMENT_SIGNAL && end->type != RAIL_ELEMENT_OPEN_TRACK) {
        error_add(error, ERROR_INTERLOCKING_ROUTE_END_NOT_SIGNAL_OR_OPEN_TRACK, "Route must end with a signal or open track");
        return;
    }

    // Check if route contains locked elements
    for (int i = 0; i < arrlen(route); i++) {
        mini_rail_element_t *element = &route[i];

        if (element->locked) {
            error_add(error, ERROR_INTERLOCKING_ROUTE_CONTAINS_LOCKED_ELEMENT, "Route contains locked element");
            return;
        }
    }

    // Set signals to stop if needed (skip starting signal)
    for (int i = 1; i < arrlen(route); i++) {
        mini_rail_element_t *element = &route[i];

        if (element->type == RAIL_ELEMENT_SIGNAL) {
            mini_rail_element_t *previous = &route[i - 1];
            bool points_to_previous = element->id == previous->id;

            if (points_to_previous) {
                rail_signal_set_stop(element->spec.signal);
                element->locked = true;
                // TODO: set signal in real world
            }
        }
    }

    // Set switches to correct position
    for (int i = 1; i < arrlen(route) - 1; i++) {
        mini_rail_element_t *element = &route[i];

        if (element->type == RAIL_ELEMENT_SWITCH) {
            mini_rail_switch_t *sw = element->spec._switch;

            mini_rail_element_t *previous = &route[i - 1];
            mini_rail_element_t *next = &route[i + 1];

            // TODO: set switch in real world
            if (previous->id == sw->left_id || next->id == sw->left_id) {
                rail_switch_set_position(sw, RAIL_SWITCH_POSITION_LEFT);
                element->locked = true;
            } else if (previous->id == sw->right_id || next->id == sw->right_id) {
                rail_switch_set_position(sw, RAIL_SWITCH_POSITION_RIGHT);
                element->locked = true;
            } else {
                rail_switch_to_base_position(sw);
            }
        }
    }

    // Set signals to clear from back to front
    for (int i = arrlen(route) - 2; i > 0; i--) {
        mini_rail_element_t *element = &route[i];

        if (element->type == RAIL_ELEMENT_SIGNAL) {
            mini_rail_element_t *next = &route[i + 1];
            bool points_to_next = element->id == next->id;

            if (points_to_next) {
                rail_signal_set_indication(element->spec.signal, RAIL_SIGNAL_INDICATION_CLEAR);
                element->locked = true;
            }
        }
    }

    // Set starting signal to clear
    rail_signal_set_indication(start->spec.signal, RAIL_SIGNAL_INDICATION_CLEAR);
    start->locked = true;
}
