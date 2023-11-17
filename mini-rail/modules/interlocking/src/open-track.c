#include <stdio.h>

#include "rail/interlocking.h"

void rail_open_track_init(mini_rail_open_track_t *open_track, int id) {
    open_track->id = id;
    open_track->display_name = "";
}

char *rail_open_track_string(mini_rail_open_track_t *open_track) {
    char *buffer = malloc(100);
    sprintf(buffer, "mini_rail_open_track_t{id=%d, display_name=\"%s\"}", open_track->id, open_track->display_name);
    return buffer;
}

void rail_open_track_print(mini_rail_open_track_t *open_track) {
    printf("%s\n", rail_open_track_string(open_track));
}
