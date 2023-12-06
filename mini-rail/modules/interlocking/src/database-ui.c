#include "rail/database.h"

void rail_database_ui_load(rail_database_t *database, ui_t *ui) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT ID FROM UI_COMPONENT;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);

        ui_component_t *component = malloc(sizeof(ui_component_t));
        ui_component_init(component, id);

        ui_line_t *lines = NULL;
        rail_database_ui_read_lines(database, id, &lines);
        component->lines = lines;

        arrput(ui->components, *component);
    }

    sqlite3_finalize(stmt);
}

void rail_database_ui_read_lines(rail_database_t *database, int component, ui_line_t **lines) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(database->db, "SELECT X_1, Y_1, X_2, Y_2, SCALE_X, SCALE_Y, COLOR FROM UI_LINE WHERE COMPONENT_ID = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, component);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int x1 = sqlite3_column_int(stmt, 0);
        int y1 = sqlite3_column_int(stmt, 1);
        int x2 = sqlite3_column_int(stmt, 2);
        int y2 = sqlite3_column_int(stmt, 3);
        float scale_x = (float)sqlite3_column_double(stmt, 4);
        float scale_y = (float)sqlite3_column_double(stmt, 5);
        char *color = (char *)sqlite3_column_text(stmt, 6);

        ui_line_t *line = malloc(sizeof(ui_line_t));
        ui_line_init(line);

        line->x1 = x1;
        line->y1 = y1;
        line->x2 = x2;
        line->y2 = y2;
        line->scale_x = scale_x;
        line->scale_y = scale_y;
        line->color = ui_color_from_string(color);

        arrput(*lines, *line);
    }

    sqlite3_finalize(stmt);
}
