#include "rail/switch.h"

void rail_switch_init(mini_rail_switch_t *switch_, int id, mini_rail_switch_position_t base_position) {
    switch_->id = id;
    switch_->base_position = base_position;
}

void rail_switch_set_position(mini_rail_switch_t *switch_, mini_rail_switch_position_t position) {
    switch_->position = position;
}

void rail_switch_to_base_position(mini_rail_switch_t *switch_) {
    switch_->base_position = switch_->base_position;
}
