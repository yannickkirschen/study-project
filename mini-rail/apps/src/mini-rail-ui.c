#define STB_DS_IMPLEMENTATION
#define ERROR_IMPLEMENTATION
#define GRAPH_IMPLEMENTATION
#define STR_IMPLEMENTATION
#define UI_IMPLEMENTATION

#include "rail/database.h"
#include "rail/ui.h"

int main() {
    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    rail_database_t *database = malloc(sizeof(rail_database_t));
    rail_database_open(database, "examples/simple-layout-1.sqlite", error);
    if (error_has_error(error)) {
        error_print(error);
        exit(1);
    }

    ui_t *ui = malloc(sizeof(ui_t));
    ui_init(ui);
    rail_database_ui_load(database, ui);

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Init SDL failed: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    int width = 800;
    int height = 600;

    window = SDL_CreateWindow("MiniRail", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        fprintf(stderr, "Init window failed: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "Init renderer failed: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_MaximizeWindow(window);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    for (int i = 0; i < arrlen(ui->components); i++) {
        ui_component_t *component = &ui->components[i];

        for (int j = 0; j < arrlen(component->lines); j++) {
            ui_line_t *line = &component->lines[j];
            ui_draw_line(renderer, line);
        }
    }

    SDL_RenderPresent(renderer);

    while (!ui_window_close_pressed()) {
    }

    return 0;
}
