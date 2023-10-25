#ifndef MINI_RAIL_SIGNAL_H
#define MINI_RAIL_SIGNAL_H

typedef enum {
    STOP,
    CLEAR
} mini_rail_signal_indication_t;

typedef struct {
    int id;
    mini_rail_signal_indication_t indication;
} mini_rail_signal_t;

void rail_signal_init(mini_rail_signal_t *signal, int id);
void rail_signal_set_indication(mini_rail_signal_t *signal, mini_rail_signal_indication_t indication);
void rail_signal_set_stop(mini_rail_signal_t *signal);

#endif  // MINI_RAIL_SIGNAL_H
