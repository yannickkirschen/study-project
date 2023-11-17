#include <stdio.h>

#include "rail/interlocking.h"

char *rail_switch_position_string(mini_rail_switch_position_t position) {
    switch (position) {
    case RAIL_SWITCH_POSITION_LEFT:
        return "LEFT";
    case RAIL_SWITCH_POSITION_RIGHT:
        return "RIGHT";
    }
}

void rail_switch_init(mini_rail_switch_t *switch_, int id, mini_rail_switch_position_t base_position, int left_id, int right_id) {
    switch_->id = id;
    switch_->display_name = "";
    switch_->base_position = base_position;
    switch_->position = base_position;
    switch_->left_id = left_id;
    switch_->right_id = right_id;
}

char *rail_switch_string(mini_rail_switch_t *switch_) {
    char *buffer = malloc(150);
    sprintf(buffer, "mini_rail_switch_t{id=%d, display_name=\"%s\", position=%s, base_position=%s, left_id=%i, right_id=%i}", switch_->id, switch_->display_name, rail_switch_position_string(switch_->position), rail_switch_position_string(switch_->base_position), switch_->left_id, switch_->right_id);
    return buffer;
}

void rail_switch_print(mini_rail_switch_t *switch_) {
    printf("%s\n", rail_switch_string(switch_));
}

void rail_switch_set_position(mini_rail_switch_t *switch_, mini_rail_switch_position_t position) {
    switch_->position = position;
}

void rail_switch_to_base_position(mini_rail_switch_t *switch_) {
    switch_->base_position = switch_->base_position;
}
