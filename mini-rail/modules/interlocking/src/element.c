#include <stdlib.h>

#include "rail/interlocking.h"

void rail_element_init(mini_rail_element_t *element, int id, mini_rail_element_type_t type) {
    element->id = id;
    element->locked = false;

    element->type = type;
    element->spec.signal = NULL;
    element->spec._switch = NULL;
    element->spec.open_track = NULL;
}

void rail_element_print(mini_rail_element_t *route) {
    for (int i = 0; i < arrlen(route); i++) {
        mini_rail_element_t *element = &route[i];

        if (element->type == RAIL_ELEMENT_SIGNAL) {
            printf("%s: %s\n", element->spec.signal->display_name, rail_signal_indication_string(element->spec.signal->indication));
        } else if (element->type == RAIL_ELEMENT_SWITCH) {
            printf("%s: %s\n", element->spec._switch->display_name, rail_switch_position_string(element->spec._switch->position));
        } else if (element->type == RAIL_ELEMENT_OPEN_TRACK) {
            printf("%s\n", element->spec.open_track->display_name);
        }
    }
}
