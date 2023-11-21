#ifndef MINI_RAIL_STR_H
#define MINI_RAIL_STR_H

#include <stdbool.h>
#include <string.h>

#include "stb_ds_helper.h"

bool string_equals(char *string1, char *string2);
bool string_starts_with(char *string, char *prefix);
void string_split(char *string, char delimiter, char ***strings);

#endif  // MINI_RAIL_STR_H
