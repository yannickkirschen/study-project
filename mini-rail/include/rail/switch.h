#ifndef MINI_RAIL_SWITCH_H
#define MINI_RAIL_SWITCH_H

typedef enum {
    LEFT,
    RIGHT
} mini_rail_switch_position_t;

typedef struct {
    int id;
    mini_rail_switch_position_t position;
    mini_rail_switch_position_t base_position;
} mini_rail_switch_t;

void rail_switch_init(mini_rail_switch_t *switch_, int id, mini_rail_switch_position_t base_position);
void rail_switch_set_position(mini_rail_switch_t *switch_, mini_rail_switch_position_t position);
void rail_switch_to_base_position(mini_rail_switch_t *switch_);

#endif  // MINI_RAIL_SWITCH_H
