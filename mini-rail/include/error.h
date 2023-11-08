#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

typedef struct {
    int *codes;
    const char **message;
} error_t;

void error_init(error_t *error);

void error_add(error_t *error, int code, const char *message);

bool error_has_error(error_t *error);

void error_print(error_t *error);

#endif  // ERROR_H
