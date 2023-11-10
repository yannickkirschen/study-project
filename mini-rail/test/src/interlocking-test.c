#include "rail/interlocking.h"

#include <stdio.h>

#include "graph.h"
#include "stb_ds_helper.h"

int main() {
    //                           /- N2(4) - P2(6) -\
    // LEFT(100) - A(1) - SW1(7) -- N1(3) - P1(5) -- SW2(8) - F(2) - RIGHT(200)

    mini_rail_signal_t *sig_A = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_A, 1);
    sig_A->display_name = "A";

    mini_rail_signal_t *sig_F = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_F, 2);
    sig_F->display_name = "F";

    mini_rail_signal_t *sig_N1 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_N1, 3);
    sig_N1->display_name = "N1";

    mini_rail_signal_t *sig_N2 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_N2, 4);
    sig_N2->display_name = "N2";

    mini_rail_signal_t *sig_P1 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_P1, 5);
    sig_P1->display_name = "P1";

    mini_rail_signal_t *sig_P2 = malloc(sizeof(mini_rail_signal_t));
    rail_signal_init(sig_P2, 6);
    sig_P2->display_name = "P2";

    mini_rail_switch_t *sw_1 = malloc(sizeof(mini_rail_switch_t));
    rail_switch_init(sw_1, 7, RAIL_SWITCH_POSITION_RIGHT, sig_N2->id, sig_N1->id);
    sw_1->display_name = "W1";

    mini_rail_switch_t *sw_2 = malloc(sizeof(mini_rail_switch_t));
    rail_switch_init(sw_2, 8, RAIL_SWITCH_POSITION_LEFT, sig_P1->id, sig_P2->id);
    sw_2->display_name = "W2";

    mini_rail_open_track_t *left = malloc(sizeof(mini_rail_open_track_t));
    rail_open_track_init(left, 100);
    left->display_name = "v.u.n. links";

    mini_rail_open_track_t *right = malloc(sizeof(mini_rail_open_track_t));
    rail_open_track_init(right, 200);
    right->display_name = "v.u.n. rechts";

    mini_rail_element_t *elem_A = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_A, 1, RAIL_ELEMENT_SIGNAL);
    elem_A->spec.signal = sig_A;

    mini_rail_element_t *elem_F = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_F, 2, RAIL_ELEMENT_SIGNAL);
    elem_F->spec.signal = sig_F;

    mini_rail_element_t *elem_N1 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_N1, 3, RAIL_ELEMENT_SIGNAL);
    elem_N1->spec.signal = sig_N1;

    mini_rail_element_t *elem_N2 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_N2, 4, RAIL_ELEMENT_SIGNAL);
    elem_N2->spec.signal = sig_N2;

    mini_rail_element_t *elem_P1 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_P1, 5, RAIL_ELEMENT_SIGNAL);
    elem_P1->spec.signal = sig_P1;

    mini_rail_element_t *elem_P2 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_P2, 6, RAIL_ELEMENT_SIGNAL);
    elem_P2->spec.signal = sig_P2;

    mini_rail_element_t *elem_SW1 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_SW1, 7, RAIL_ELEMENT_SWITCH);
    elem_SW1->spec._switch = sw_1;

    mini_rail_element_t *elem_SW2 = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_SW2, 8, RAIL_ELEMENT_SWITCH);
    elem_SW2->spec._switch = sw_2;

    mini_rail_element_t *elem_LEFT = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_LEFT, 100, RAIL_ELEMENT_OPEN_TRACK);
    elem_LEFT->spec.open_track = left;

    mini_rail_element_t *elem_RIGHT = malloc(sizeof(mini_rail_element_t));
    rail_element_init(elem_RIGHT, 200, RAIL_ELEMENT_OPEN_TRACK);
    elem_RIGHT->spec.open_track = right;

    mini_rail_interlocking_t *interlocking = malloc(sizeof(mini_rail_interlocking_t));
    rail_interlocking_init(interlocking);

    rail_interlocking_element_add(interlocking, sig_A->id, elem_A);
    rail_interlocking_element_add(interlocking, sig_F->id, elem_F);
    rail_interlocking_element_add(interlocking, sig_N1->id, elem_N1);
    rail_interlocking_element_add(interlocking, sig_N2->id, elem_N2);
    rail_interlocking_element_add(interlocking, sig_P1->id, elem_P1);
    rail_interlocking_element_add(interlocking, sig_P2->id, elem_P2);
    rail_interlocking_element_add(interlocking, sw_1->id, elem_SW1);
    rail_interlocking_element_add(interlocking, sw_2->id, elem_SW2);
    rail_interlocking_element_add(interlocking, left->id, elem_LEFT);
    rail_interlocking_element_add(interlocking, right->id, elem_RIGHT);

    elem_A->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_A->points_to_spec._switch = sw_1;

    elem_F->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_F->points_to_spec._switch = sw_2;

    elem_N1->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_N1->points_to_spec._switch = sw_1;

    elem_N2->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_N2->points_to_spec._switch = sw_1;

    elem_P1->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_P1->points_to_spec._switch = sw_2;

    elem_P2->points_to_type = RAIL_ELEMENT_SWITCH;
    elem_P2->points_to_spec._switch = sw_2;

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

    interlocking->graph = graph;

    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    mini_rail_element_t *route = rail_interlocking_route_find_and_set(interlocking, sig_A->id, sig_P2->id, error);
    error_print(error);
    rail_element_print(route);

    return 0;
}
