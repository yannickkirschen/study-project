#ifndef STD_DS_HELPER_H
#define STD_DS_HELPER_H

#include <stdbool.h>
#include <stdio.h>

#include "stb_ds.h"

bool stb_ds_array_contains(const int *a, int b);
int *stb_ds_array_copy(const int *a);
void stb_ds_array_remove(int **a, int b);
void stb_ds_array_remove_last(int **a);
void stb_ds_array_print(int *a);
void stb_ds_array_print_two_dimensional(int **a);

#ifdef STB_DS_IMPLEMENTATION

bool stb_ds_array_contains(const int *a, int b) {
    for (int i = 0; i < arrlen(a); i++) {
        if (a[i] == b) {
            return true;
        }
    }

    return false;
}

int *stb_ds_array_copy(const int *a) {
    int *b = NULL;
    for (int i = 0; i < arrlen(a); i++) {
        arrput(b, a[i]);
    }
    return b;
}

void stb_ds_array_remove(int **a, int b) {
    for (int i = 0; i < arrlen(*a); i++) {
        if ((*a)[i] == b) {
            arrdel(*a, i);
            return;
        }
    }
}

void stb_ds_array_remove_last(int **a) {
    arrdel(*a, arrlen(*a) - 1);
}

void stb_ds_array_print(int *a) {
    printf("[");
    for (int i = 0; i < arrlen(a); i++) {
        printf("%i", a[i]);

        if (i < arrlen(a) - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void stb_ds_array_print_two_dimensional(int **a) {
    printf("[\n");
    for (int i = 0; i < arrlen(a); i++) {
        int *b = a[i];

        printf("    [");
        for (int j = 0; j < arrlen(b); j++) {
            printf("%i", b[j]);

            if (j < arrlen(b) - 1) {
                printf(", ");
            }
        }
        printf("]");

        if (i < arrlen(a) - 1) {
            printf(",\n");
        }
    }
    printf("\n]\n");
}

#endif  // STB_DS_IMPLEMENTATION

#endif  // STD_DS_HELPER_H
