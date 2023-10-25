#include "rail/error.h"

#include <stdlib.h>

void rail_error_init(rail_error_t *error) {
    error->code = 0;
    error->message = NULL;
}

void rail_error_add(rail_error_t *error, int code, const char *message) {
    error->code = code;
    error->message = message;
}

bool rail_error_has_error(rail_error_t *error) {
    return error->message != NULL && error->code != 0;
}
