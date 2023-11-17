#include "rail/interlocking.h"

mini_rail_element_type_t rail_element_type_from_string(char *string) {
    if (strcmp(string, "signal") == 0) {
        return RAIL_ELEMENT_SIGNAL;
    } else if (strcmp(string, "switch") == 0) {
        return RAIL_ELEMENT_SWITCH;
    } else if (strcmp(string, "open_track") == 0) {
        return RAIL_ELEMENT_OPEN_TRACK;
    }

    return RAIL_ELEMENT_NONE;
}

char *rail_element_type_string(mini_rail_element_type_t type) {
    switch (type) {
    case RAIL_ELEMENT_SIGNAL:
        return "signal";
    case RAIL_ELEMENT_SWITCH:
        return "switch";
    case RAIL_ELEMENT_OPEN_TRACK:
        return "open_track";
    case RAIL_ELEMENT_NONE:
    default:
        return "none";
    }
}

void rail_element_init(mini_rail_element_t *element, int id, mini_rail_element_type_t type) {
    element->id = id;
    element->locked = false;

    element->type = type;
    element->spec.signal = NULL;
    element->spec._switch = NULL;
    element->spec.open_track = NULL;

    element->points_to_type = RAIL_ELEMENT_NONE;
    element->points_to_spec.signal = NULL;
    element->points_to_spec._switch = NULL;
    element->points_to_spec.open_track = NULL;
}

void rail_element_print(mini_rail_element_t *element) {
    char *spec_string = NULL;
    if (element->type == RAIL_ELEMENT_SIGNAL) {
        spec_string = rail_signal_string(element->spec.signal);
    } else if (element->type == RAIL_ELEMENT_SWITCH) {
        spec_string = rail_switch_string(element->spec._switch);
    } else if (element->type == RAIL_ELEMENT_OPEN_TRACK) {
        spec_string = rail_open_track_string(element->spec.open_track);
    } else {
        spec_string = "";
    }

    char *points_to_spec_string = NULL;
    if (element->points_to_type == RAIL_ELEMENT_SIGNAL) {
        points_to_spec_string = rail_signal_string(element->points_to_spec.signal);
    } else if (element->points_to_type == RAIL_ELEMENT_SWITCH) {
        points_to_spec_string = rail_switch_string(element->points_to_spec._switch);
    } else if (element->points_to_type == RAIL_ELEMENT_OPEN_TRACK) {
        points_to_spec_string = rail_open_track_string(element->points_to_spec.open_track);
    } else {
        points_to_spec_string = "";
    }

    printf("mini_rail_element_t{id=%d, locked=%d, type=%s, spec=%s, points_to_type=%s, points_to_spec=%s}\n", element->id, element->locked, rail_element_type_string(element->type), spec_string, rail_element_type_string(element->points_to_type), points_to_spec_string);
}

void rail_elements_print(mini_rail_element_t *elements) {
    for (int i = 0; i < arrlen(elements); i++) {
        mini_rail_element_t *element = &elements[i];
        rail_element_print(element);
    }
}
