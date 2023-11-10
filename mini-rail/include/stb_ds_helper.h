#ifndef STD_DS_HELPER_H
#define STD_DS_HELPER_H

#include <stdbool.h>
#include <stdio.h>

#include "stb_ds.h"

bool stb_ds_array_contains(const int *a, int b);
int *stb_ds_array_copy(const int *a);
void stb_ds_array_remove(int **a, int b);
void stb_ds_array_remove_last(int **a);
void stb_array_print(int *a);
void stb_array_print_two_dimensional(int **a);

#endif  // STD_DS_HELPER_H
