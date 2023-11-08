#include "error.h"

#include <stdio.h>

#include "stb_ds.h"

void error_init(error_t *error) {
    error->codes = NULL;
    error->message = NULL;
}

void error_add(error_t *error, int code, const char *message) {
    arrput(error->codes, code);
    arrput(error->message, message);
}

bool error_has_error(error_t *error) {
    return error->message != NULL && error->codes != NULL;
}

void error_print(error_t *error) {
    if (error_has_error(error)) {
        printf("%ti error(s) occurred:\n", arrlen(error->message));
        for (int i = 0; i < arrlen(error->message); i++) {
            printf("  [%i]: %s\n", error->codes[i], error->message[i]);
        }
    }
}
