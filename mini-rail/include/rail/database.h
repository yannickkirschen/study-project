#ifndef MINI_RAIL_DATABASE_H
#define MINI_RAIL_DATABASE_H

#include <sqlite3.h>

#include "error.h"
#include "rail/interlocking.h"

#define ERROR_DATABASE_OPEN 1

typedef struct {
    sqlite3 *db;
} rail_database_t;

void rail_database_open(rail_database_t *database, char *file, error_t *error);
void rail_database_close(rail_database_t *database);

void rail_database_find_signal_by_id(rail_database_t *database, int id, mini_rail_signal_t *signal);
void rail_database_read_signals(rail_database_t *database, mini_rail_signal_t **signals);

void rail_database_find_switch_by_id(rail_database_t *database, int id, mini_rail_switch_t *switch_);
void rail_database_read_switches(rail_database_t *database, mini_rail_switch_t **switches);

void rail_database_find_open_track_by_id(rail_database_t *database, int id, mini_rail_open_track_t *open_track);
void rail_database_read_open_tracks(rail_database_t *database, mini_rail_open_track_t **open_tracks);

void rail_database_read_elements(rail_database_t *database, mini_rail_element_t **elements);

void rail_database_read_graph(rail_database_t *database, graph_t *graph);

void rail_database_interlocking_load(mini_rail_interlocking_t *interlocking, rail_database_t *database, error_t *error);

#endif  // MINI_RAIL_DATABASE_H
