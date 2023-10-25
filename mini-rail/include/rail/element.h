#ifndef MINI_RAIL_ELEMENT_H
#define MINI_RAIL_ELEMENT_H

#include <stdbool.h>

#include "rail/signal.h"
#include "rail/switch.h"

typedef enum {
    SIGNAL,
    SWITCH
} mini_rail_element_type_t;

typedef struct {
    int id;
    bool locked;

    mini_rail_element_type_t type;
    union {
        mini_rail_signal_t *signal;
        mini_rail_switch_t *_switch;
    } spec;
} mini_rail_element_t;

#endif  // MINI_RAIL_ELEMENT_H
