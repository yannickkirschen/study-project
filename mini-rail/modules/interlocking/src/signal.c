#include <stdio.h>

#include "rail/interlocking.h"

char *rail_signal_indication_string(mini_rail_signal_indication_t indication) {
    switch (indication) {
    case RAIL_SIGNAL_INDICATION_STOP:
        return "STOP";
    case RAIL_SIGNAL_INDICATION_CLEAR:
        return "CLEAR";
    }
}

void rail_signal_init(mini_rail_signal_t *signal, int id) {
    signal->id = id;
    signal->display_name = "";
    signal->indication = RAIL_SIGNAL_INDICATION_STOP;
}

char *rail_signal_string(mini_rail_signal_t *signal) {
    char *buffer = malloc(100);
    sprintf(buffer, "mini_rail_signal_t{id=%d, display_name=\"%s\", indication=%s}", signal->id, signal->display_name, rail_signal_indication_string(signal->indication));
    return buffer;
}

void rail_signal_print(mini_rail_signal_t *signal) {
    printf("%s\n", rail_signal_string(signal));
}

void rail_signal_set_indication(mini_rail_signal_t *signal, mini_rail_signal_indication_t indication) {
    signal->indication = indication;
}

void rail_signal_set_stop(mini_rail_signal_t *signal) {
    signal->indication = RAIL_SIGNAL_INDICATION_STOP;
}
