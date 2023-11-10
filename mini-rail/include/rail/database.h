#ifndef MINI_RAIL_DATABASE_H
#define MINI_RAIL_DATABASE_H

#include <sqlite3.h>

#include "error.h"
#include "rail/interlocking.h"

#define ERROR_DATABASE_OPEN 1

typedef struct {
    sqlite3 *db;
} database_t;

void database_open(database_t *database, char *file, error_t *error);
void database_close(database_t *database);

void database_read_signals(database_t *database, mini_rail_signal_t **signals);
void database_read_switches(database_t *database, mini_rail_switch_t **switches);
void database_read_open_tracks(database_t *database, mini_rail_open_track_t **open_tracks);

#endif  // MINI_RAIL_DATABASE_H
