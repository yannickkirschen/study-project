#include "rail/database.h"

#include <string.h>

#include "stb_ds_helper.h"

void database_open(database_t *database, char *file, error_t *error) {
    int rc = sqlite3_open(file, &database->db);
    if (rc) {
        error_add(error, ERROR_DATABASE_OPEN, sqlite3_errmsg(database->db));
        return;
    }
}

void database_close(database_t *database) {
    sqlite3_close(database->db);
}

void database_read_signals(database_t *database, mini_rail_signal_t **signals) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME, INDICATION FROM SIGNAL;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *display_name = (char *)sqlite3_column_text(stmt, 1);
        int indication = sqlite3_column_int(stmt, 2);

        mini_rail_signal_t *signal = malloc(sizeof(mini_rail_signal_t));
        rail_signal_init(signal, id);
        signal->indication = indication;

        signal->display_name = malloc(strlen(display_name) + 1);
        strcpy(signal->display_name, display_name);

        arrput(*signals, *signal);
    }

    sqlite3_finalize(stmt);
}

void database_read_switches(database_t *database, mini_rail_switch_t **switches) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID, DISPLAY_NAME, POSITION, BASE_POSITION, LEFT_ID, RIGHT_ID FROM SWITCH;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *display_name = (char *)sqlite3_column_text(stmt, 1);
        int position = sqlite3_column_int(stmt, 2);
        int base_position = sqlite3_column_int(stmt, 3);
        int left_id = sqlite3_column_int(stmt, 4);
        int right_id = sqlite3_column_int(stmt, 5);

        mini_rail_switch_t *switch_ = malloc(sizeof(mini_rail_switch_t));
        rail_switch_init(switch_, id, base_position, left_id, right_id);
        switch_->position = position;

        switch_->display_name = malloc(strlen(display_name) + 1);
        strcpy(switch_->display_name, display_name);

        arrput(*switches, *switch_);
    }

    sqlite3_finalize(stmt);
}

void database_read_open_tracks(database_t *database, mini_rail_open_track_t **open_tracks) {
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
