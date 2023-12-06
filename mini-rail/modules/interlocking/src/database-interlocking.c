#include "rail/database.h"

#include <string.h>

#include "stb_ds_helper.h"

void rail_database_open(rail_database_t *database, char *file, error_t *error) {
    int rc = sqlite3_open(file, &database->db);
    if (rc) {
        error_add(error, ERROR_DATABASE_OPEN, sqlite3_errmsg(database->db));
        return;
    }
}

void rail_database_close(rail_database_t *database) {
    sqlite3_close(database->db);
}

void rail_database_find_signal_by_id(rail_database_t *database, int id, mini_rail_signal_t *signal) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME FROM SIGNAL WHERE ID = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        char *display_name = (char *)sqlite3_column_text(stmt, 1);

        rail_signal_init(signal, id);

        signal->display_name = malloc(strlen(display_name) + 1);
        strcpy(signal->display_name, display_name);
    }

    sqlite3_finalize(stmt);
}

void rail_database_read_signals(rail_database_t *database, mini_rail_signal_t **signals) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME FROM SIGNAL;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *display_name = (char *)sqlite3_column_text(stmt, 1);

        mini_rail_signal_t *signal = malloc(sizeof(mini_rail_signal_t));
        rail_signal_init(signal, id);

        signal->display_name = malloc(strlen(display_name) + 1);
        strcpy(signal->display_name, display_name);

        arrput(*signals, *signal);
    }

    sqlite3_finalize(stmt);
}

void rail_database_find_switch_by_id(rail_database_t *database, int id, mini_rail_switch_t *switch_) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME, BASE_POSITION, LEFT_ID, RIGHT_ID FROM SWITCH WHERE ID = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        char *display_name = (char *)sqlite3_column_text(stmt, 1);
        int base_position = sqlite3_column_int(stmt, 2);
        int left_id = sqlite3_column_int(stmt, 3);
        int right_id = sqlite3_column_int(stmt, 4);

        rail_switch_init(switch_, id, base_position, left_id, right_id);

        switch_->display_name = malloc(strlen(display_name) + 1);
        strcpy(switch_->display_name, display_name);
    }

    sqlite3_finalize(stmt);
}

void rail_database_read_switches(rail_database_t *database, mini_rail_switch_t **switches) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME, BASE_POSITION, LEFT_ID, RIGHT_ID FROM SWITCH;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *display_name = (char *)sqlite3_column_text(stmt, 1);
        int base_position = sqlite3_column_int(stmt, 2);
        int left_id = sqlite3_column_int(stmt, 3);
        int right_id = sqlite3_column_int(stmt, 4);

        mini_rail_switch_t *switch_ = malloc(sizeof(mini_rail_switch_t));
        rail_switch_init(switch_, id, base_position, left_id, right_id);

        switch_->display_name = malloc(strlen(display_name) + 1);
        strcpy(switch_->display_name, display_name);

        arrput(*switches, *switch_);
    }

    sqlite3_finalize(stmt);
}

void rail_database_find_open_track_by_id(rail_database_t *database, int id, mini_rail_open_track_t *open_track) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME FROM OPEN_TRACK WHERE ID = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        char *display_name = (char *)sqlite3_column_text(stmt, 1);

        rail_open_track_init(open_track, id);

        open_track->display_name = malloc(strlen(display_name) + 1);
        strcpy(open_track->display_name, display_name);
    }

    sqlite3_finalize(stmt);
}

void rail_database_read_open_tracks(rail_database_t *database, mini_rail_open_track_t **open_tracks) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME FROM OPEN_TRACK;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *display_name = (char *)sqlite3_column_text(stmt, 1);

        mini_rail_open_track_t *open_track = malloc(sizeof(mini_rail_open_track_t));
        rail_open_track_init(open_track, id);

        open_track->display_name = malloc(strlen(display_name) + 1);
        strcpy(open_track->display_name, display_name);

        arrput(*open_tracks, *open_track);
    }

    sqlite3_finalize(stmt);
}

void rail_database_read_elements(rail_database_t *database, mini_rail_element_t **elements) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db,
                       "SELECT E.ID, E.ELEMENT_TYPE, SIG.POINTS_TO_TYPE, SIG.POINTS_TO\n"
                       "FROM ELEMENT E\n"
                       "LEFT OUTER JOIN SIGNAL SIG ON E.ID = SIG.ID\n"
                       "LEFT OUTER JOIN SWITCH SW ON E.ID = SW.ID\n"
                       "LEFT OUTER JOIN OPEN_TRACK OT ON E.ID = OT.ID;",
                       -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *element_type = (char *)sqlite3_column_text(stmt, 1);
        char *points_to_type = (char *)sqlite3_column_text(stmt, 2);
        int points_to = sqlite3_column_int(stmt, 3);

        mini_rail_element_t *element = malloc(sizeof(mini_rail_element_t));
        rail_element_init(element, id, rail_element_type_from_string(element_type));

        if (element->type == RAIL_ELEMENT_SIGNAL) {
            element->spec.signal = malloc(sizeof(mini_rail_signal_t));
            rail_database_find_signal_by_id(database, id, element->spec.signal);
        } else if (element->type == RAIL_ELEMENT_SWITCH) {
            element->spec._switch = malloc(sizeof(mini_rail_switch_t));
            rail_database_find_switch_by_id(database, id, element->spec._switch);
        } else if (element->type == RAIL_ELEMENT_OPEN_TRACK) {
            element->spec.open_track = malloc(sizeof(mini_rail_open_track_t));
            rail_database_find_open_track_by_id(database, id, element->spec.open_track);
        }

        if (points_to_type != NULL) {
            element->points_to_type = rail_element_type_from_string(points_to_type);

            if (element->points_to_type == RAIL_ELEMENT_SIGNAL) {
                element->points_to_spec.signal = malloc(sizeof(mini_rail_signal_t));
                rail_database_find_signal_by_id(database, points_to, element->points_to_spec.signal);
            } else if (element->points_to_type == RAIL_ELEMENT_SWITCH) {
                element->points_to_spec._switch = malloc(sizeof(mini_rail_switch_t));
                rail_database_find_switch_by_id(database, points_to, element->points_to_spec._switch);
            } else if (element->points_to_type == RAIL_ELEMENT_OPEN_TRACK) {
                element->points_to_spec.open_track = malloc(sizeof(mini_rail_open_track_t));
                rail_database_find_open_track_by_id(database, points_to, element->points_to_spec.open_track);
            }
        } else {
            element->points_to_type = RAIL_ELEMENT_NONE;
        }

        arrput(*elements, *element);
    }
}

void rail_database_read_graph(rail_database_t *database, graph_t *graph) {
    sqlite3_stmt *stmt_vertices;
    sqlite3_prepare_v2(database->db, "SELECT DISTINCT VERTEX FROM GRAPH;", -1, &stmt_vertices, NULL);

    while (sqlite3_step(stmt_vertices) == SQLITE_ROW) {
        int vertex = sqlite3_column_int(stmt_vertices, 0);
        graph_vertex_add(graph, &(graph_vertex_t){.key = vertex, .value = NULL});
    }

    sqlite3_stmt *stmt_edges;
    sqlite3_prepare_v2(database->db, "SELECT VERTEX, EDGE FROM GRAPH;", -1, &stmt_edges, NULL);

    while (sqlite3_step(stmt_edges) == SQLITE_ROW) {
        int vertex = sqlite3_column_int(stmt_edges, 0);
        int edge = sqlite3_column_int(stmt_edges, 1);

        graph_vertex_t *edge_1 = &graph->adjacency_list[hmgeti(graph->adjacency_list, vertex)];
        graph_vertex_t *edge_2 = &graph->adjacency_list[hmgeti(graph->adjacency_list, edge)];

        graph_edge_add(graph, edge_1, edge_2);
    }
}

void rail_database_interlocking_load(mini_rail_interlocking_t *interlocking, rail_database_t *database, error_t *error) {
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
    interlocking->graph = graph;

    for (int i = 0; i < arrlen(elements); i++) {
        rail_interlocking_element_add(interlocking, elements[i].id, &elements[i]);
    }
}
