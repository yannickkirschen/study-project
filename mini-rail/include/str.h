#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <string.h>

#include "stb_ds_helper.h"

bool string_equals(char *string1, char *string2);
bool string_equals_ignore_case(char *string1, char *string2);
bool string_starts_with(char *string, char *prefix);
void string_split(char *string, char delimiter, char ***strings);
char *string_trim(char *string);

#ifdef STR_IMPLEMENTATION

bool string_equals(char *string1, char *string2) {
    return strcmp(string1, string2) == 0;
}

bool string_equals_ignore_case(char *string1, char *string2) {
    return strcasecmp(string1, string2) == 0;
}

bool string_starts_with(char *string, char *prefix) {
    return strncmp(string, prefix, strlen(prefix)) == 0;
}

void string_split(char *string, char delimiter, char ***strings) {
    char c;
    char *s = NULL;

    do {
        c = *string++;
        if (c == delimiter) {
            arrput(*strings, s);
            s = NULL;
        } else {
            arrput(s, c);
        }
    } while (c != '\0');

    arrput(*strings, s);
}

char *string_trim(char *string) {
    char *trimmed = malloc(strlen(string) + 1);
    strcpy(string, trimmed);
    return trimmed;
}

#endif  // STR_IMPLEMENTATION

#endif  // STR_H
