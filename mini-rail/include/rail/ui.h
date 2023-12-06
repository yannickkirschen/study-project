#ifndef MINI_RAIL_UI_H
#define MINI_RAIL_UI_H

#include "SDL2/SDL.h"
#include "stb_ds_helper.h"

int ui_window_close_pressed();

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} ui_color_t;

ui_color_t *ui_color_from_string(char *string);
void ui_color_print(ui_color_t *color);

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;

    float scale_x;
    float scale_y;

    ui_color_t *color;
} ui_line_t;

void ui_line_init(ui_line_t *line);
void ui_draw_line(SDL_Renderer *renderer, ui_line_t *line);

typedef struct {
    uint32_t id;
    ui_line_t *lines;
} ui_component_t;

void ui_component_init(ui_component_t *component, uint32_t id);

typedef struct {
    ui_component_t *components;
} ui_t;

void ui_init(ui_t *ui);

#ifdef UI_IMPLEMENTATION

int ui_window_close_pressed() {
    SDL_Event key_event;
    SDL_PollEvent(&key_event);
    return key_event.type == SDL_QUIT;
}

ui_color_t *ui_color_from_string(char *string) {
    ui_color_t *color = malloc(sizeof(ui_color_t));

    if (string_equals_ignore_case(string, "white")) {
        color->r = 255;
        color->g = 255;
        color->b = 255;
        color->a = 255;
    } else if (string_equals_ignore_case(string, "red")) {
        color->r = 255;
        color->g = 0;
        color->b = 0;
        color->a = 255;
    } else if (string_equals_ignore_case(string, "green")) {
        color->r = 0;
        color->g = 255;
        color->b = 0;
        color->a = 255;
    } else if (string_equals_ignore_case(string, "blue")) {
        color->r = 0;
        color->g = 0;
        color->b = 255;
        color->a = 255;
    } else if (string_equals_ignore_case(string, "yellow")) {
        color->r = 255;
        color->g = 255;
        color->b = 0;
        color->a = 255;
    } else {
        color->r = 0;
        color->g = 0;
        color->b = 0;
        color->a = 255;
    }

    return color;
}

void ui_color_print(ui_color_t *color) {
    printf("ui_color_t{r=%d, g=%d, b=%d, a=%d}\n", color->r, color->g, color->b, color->a);
}

void ui_line_init(ui_line_t *line) {
    line->x1 = 0;
    line->y1 = 0;
    line->x2 = 0;
    line->y2 = 0;
    line->scale_x = 1;
    line->scale_y = 1;
    line->color = NULL;
}

void ui_draw_line(SDL_Renderer *renderer, ui_line_t *line) {
    SDL_SetRenderDrawColor(renderer, line->color->r, line->color->g, line->color->b, line->color->a);

    SDL_RenderSetScale(renderer, line->scale_x, line->scale_y);
    SDL_RenderDrawLine(renderer, line->x1, line->y1, line->x2, line->y2);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void ui_component_init(ui_component_t *component, uint32_t id) {
    component->id = id;
    component->lines = NULL;
}

void ui_init(ui_t *ui) {
    ui->components = NULL;
}

#endif  // UI_IMPLEMENTATION

#endif  // MINI_RAIL_UI_H
