#ifndef MINI_RAIL_CONTROLLER_H
#define MINI_RAIL_CONTROLLER_H

#include <stdint.h>

#define MINI_RAIL_CONTROLLER_STATE_STARTUP 0
#define MINI_RAIL_CONTROLLER_STATE_READY 1
#define MINI_RAIL_CONTROLLER_STATE_INIT 2
#define MINI_RAIL_CONTROLLER_STATE_RUNNING 3

typedef struct {
    uint32_t state;
} mini_rail_controller_t;

void mini_rail_controller_init(mini_rail_controller_t *controller);

#ifdef MINI_RAIL_CONTROLLER_IMPLEMENTATION

void mini_rail_controller_init(mini_rail_controller_t *controller) {
    controller->state = MINI_RAIL_CONTROLLER_STATE_STARTUP;
}

#endif  // MINI_RAIL_CONTROLLER_IMPLEMENTATION

#endif  // MINI_RAIL_CONTROLLER_H
