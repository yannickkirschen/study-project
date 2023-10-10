#ifndef RAIL_ERROR_H
#define RAIL_ERROR_H

#include <stdbool.h>

struct rail_error {
    const char** messages;
    int number_messages;
} typedef rail_error;

void rail_error_init(rail_error* error);

void rail_error_add(rail_error* error, const char* message);

bool rail_error_has_error(rail_error* error);

#endif  // RAIL_ERROR_H
