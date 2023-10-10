#include "rail/error.h"

#include <stdlib.h>

void rail_error_init(rail_error* error) {
    error->messages = malloc(sizeof(char*));
    error->number_messages = 0;
}

void rail_error_add(rail_error* error, const char* message) {
    const char** new_messages = malloc(sizeof(char*) * (error->number_messages + 1));
    for (int i = 0; i < error->number_messages; i++) {
        new_messages[i] = error->messages[i];
    }
    new_messages[error->number_messages] = message;

    free(error->messages);
    error->messages = new_messages;
    error->number_messages++;
}

bool rail_error_has_error(rail_error* error) {
    return error->number_messages == 0;
}
