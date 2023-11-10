#include <stdio.h>

#include "rail/interlocking.h"

void rail_open_track_init(mini_rail_open_track_t *open_track, int id) {
    open_track->id = id;
    open_track->display_name = "";
}

void rail_open_track_print(mini_rail_open_track_t *open_track) {
    printf("mini_rail_open_track_t{id=%d, display_name=\"%s\"}\n", open_track->id, open_track->display_name);
}
