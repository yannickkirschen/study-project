#include "rail/signal.h"

void rail_signal_init(mini_rail_signal_t *signal, int id) {
    signal->id = id;
    signal->indication = STOP;
}

void rail_signal_set_indication(mini_rail_signal_t *signal, mini_rail_signal_indication_t indication) {
    signal->indication = indication;
}

void rail_signal_set_stop(mini_rail_signal_t *signal) {
    signal->indication = STOP;
}
