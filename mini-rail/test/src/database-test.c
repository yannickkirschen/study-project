#define STR_IMPLEMENTATION
#define GRAPH_IMPLEMENTATION
#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#include "rail/database.h"

#include <stdlib.h>

#include "stb_ds_helper.h"

int main() {
    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    rail_database_t *database = malloc(sizeof(rail_database_t));
    rail_database_open(database, "examples/simple-layout-1.sqlite", error);
    error_print(error);

    mini_rail_signal_t *signals = NULL;
    rail_database_read_signals(database, &signals);

    mini_rail_switch_t *switches = NULL;
    rail_database_read_switches(database, &switches);

    mini_rail_open_track_t *open_tracks = NULL;
    rail_database_read_open_tracks(database, &open_tracks);

    mini_rail_element_t *elements = NULL;
    rail_database_read_elements(database, &elements);

    graph_t *graph = malloc(sizeof(graph_t));
    graph_init(graph);

    rail_database_read_graph(database, graph);

    for (int i = 0; i < arrlen(signals); i++) {
        rail_signal_print(&signals[i]);
    }

    for (int i = 0; i < arrlen(switches); i++) {
        rail_switch_print(&switches[i]);
    }

    for (int i = 0; i < arrlen(open_tracks); i++) {
        rail_open_track_print(&open_tracks[i]);
    }

    rail_elements_print(elements);

    int **paths = graph_find_paths(graph, 1, 6);
    stb_array_print_two_dimensional(paths);

    rail_database_close(database);
}
