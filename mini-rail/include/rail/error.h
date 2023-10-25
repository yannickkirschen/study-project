#ifndef MINI_RAIL_ERROR_H
#define MINI_RAIL_ERROR_H

#include <stdbool.h>

typedef struct {
    int code;
    const char *message;
} rail_error_t;

void rail_error_init(rail_error_t *error);

void rail_error_add(rail_error_t *error, int code, const char *message);

bool rail_error_has_error(rail_error_t *error);

#endif  // MINI_RAIL_ERROR_H
