#include "graph.h"

#include <stdlib.h>

#include "rail/interlocking.h"
#include "stb_ds_helper.h"

int main() {
    mini_rail_signal_t *sig_A = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_A, 1);

    mini_rail_signal_t *sig_F = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_F, 2);

    mini_rail_signal_t *sig_N1 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_N1, 3);

    mini_rail_signal_t *sig_N2 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_N2, 4);

    mini_rail_signal_t *sig_P1 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_P1, 5);

    mini_rail_signal_t *sig_P2 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_P2, 6);

    mini_rail_switch_t *sw_1 = malloc(sizeof(mini_rail_switch_t));
    rail_switch_init(sw_1, 7, RAIL_SWITCH_POSITION_RIGHT, sig_N2->id, sig_N1->id);

    mini_rail_switch_t *sw_2 = malloc(sizeof(mini_rail_switch_t));
    rail_switch_init(sw_2, 8, RAIL_SWITCH_POSITION_LEFT, sig_P1->id, sig_P2->id);

    graph_t *graph = malloc(sizeof(graph_t));
    graph_init(graph);

    graph_vertex_t *vertex1 = &(graph_vertex_t){.key = sig_A->id, .value = sig_A};
    graph_vertex_t *vertex2 = &(graph_vertex_t){.key = sig_F->id, .value = sig_F};
    graph_vertex_t *vertex3 = &(graph_vertex_t){.key = sig_N1->id, .value = sig_N1};
    graph_vertex_t *vertex4 = &(graph_vertex_t){.key = sig_N2->id, .value = sig_N2};
    graph_vertex_t *vertex5 = &(graph_vertex_t){.key = sig_P1->id, .value = sig_P1};
    graph_vertex_t *vertex6 = &(graph_vertex_t){.key = sig_P2->id, .value = sig_P2};
    graph_vertex_t *vertex7 = &(graph_vertex_t){.key = sw_1->id, .value = sw_1};
    graph_vertex_t *vertex8 = &(graph_vertex_t){.key = sw_2->id, .value = sw_2};

    graph_vertex_add(graph, vertex1);
    graph_vertex_add(graph, vertex2);
    graph_vertex_add(graph, vertex3);
    graph_vertex_add(graph, vertex4);
    graph_vertex_add(graph, vertex5);
    graph_vertex_add(graph, vertex6);
    graph_vertex_add(graph, vertex7);
    graph_vertex_add(graph, vertex8);

    graph_edge_add(graph, vertex1, vertex7);
    graph_edge_add(graph, vertex7, vertex3);
    graph_edge_add(graph, vertex7, vertex4);
    graph_edge_add(graph, vertex3, vertex5);
    graph_edge_add(graph, vertex4, vertex6);
    graph_edge_add(graph, vertex5, vertex8);
    graph_edge_add(graph, vertex6, vertex8);
    graph_edge_add(graph, vertex8, vertex2);

    graph_print(graph);

    int **paths = graph_find_paths(graph, vertex1->key, vertex6->key);
    stb_array_print_two_dimensional(paths);

    return 0;
}
