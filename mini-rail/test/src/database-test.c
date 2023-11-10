#include "rail/database.h"

#include <stdio.h>
#include <stdlib.h>

#include "stb_ds_helper.h"

int main() {
    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    database_t *database = malloc(sizeof(database_t));
    database_open(database, "examples/simple-layout-1.sqlite", error);
    error_print(error);

    mini_rail_signal_t *signals = NULL;
    database_read_signals(database, &signals);

    mini_rail_switch_t *switches = NULL;
    database_read_switches(database, &switches);

    mini_rail_open_track_t *open_tracks = NULL;
    database_read_open_tracks(database, &open_tracks);

    for (int i = 0; i < arrlen(signals); i++) {
        rail_signal_print(&signals[i]);
    }

    for (int i = 0; i < arrlen(switches); i++) {
        rail_switch_print(&switches[i]);
    }

    for (int i = 0; i < arrlen(open_tracks); i++) {
        rail_open_track_print(&open_tracks[i]);
    }

    database_close(database);
}
