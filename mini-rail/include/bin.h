#ifndef BIN_H
#define BIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t *data;
    size_t size;
} bin_uint8_array_t;

bin_uint8_array_t *bin_string_to_uint8_array(char *string);
char *bin_uint8_array_to_string(const uint8_t *array, size_t size);

uint32_t bin_string_to_uint32(char *string);
char *bin_uint32_to_string(uint32_t value);

uint64_t bin_string_to_uint64(char *string);
char *bin_uint64_to_string(uint64_t value);

#ifdef BIN_IMPLEMENTATION

bin_uint8_array_t *bin_string_to_uint8_array(char *string) {
    size_t size = strlen(string) / 8;
    uint8_t *result = malloc(size);

    for (int i = 0; i < size; i++) {
        result[i] = 0;
        for (int j = 0; j < 8; j++) {
            if (string[i * 8 + j] == '1') {
                result[i] = result[i] | (1 << (7 - j));
            }
        }
    }

    bin_uint8_array_t *array = malloc(sizeof(bin_uint8_array_t));
    array->data = result;
    array->size = size;
    return array;
}

char *bin_uint8_array_to_string(const uint8_t *array, size_t size) {
    char *result = malloc(size * 9);
    result[size * 8] = '\0';
    for (int i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            if (array[i] & (1 << j)) {
                result[i * 8 + 7 - j] = '1';
            } else {
                result[i * 8 + 7 - j] = '0';
            }
        }
    }

    return result;
}

uint32_t bin_string_to_uint32(char *string) {
    uint32_t result = 0;
    for (int i = 0; i < strlen(string); i++) {
        result = result << 1;
        if (string[i] == '1') {
            result = result | 1;
        }
    }

    return result;
}

char *bin_uint32_to_string(uint32_t value) {
    char *result = malloc(33);
    result[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        if (value & (1 << i)) {
            result[31 - i] = '1';
        } else {
            result[31 - i] = '0';
        }
    }

    return result;
}

uint64_t bin_string_to_uint64(char *string) {
    uint64_t result = 0;
    for (int i = 0; i < strlen(string); i++) {
        result = result << 1;
        if (string[i] == '1') {
            result = result | 1;
        }
    }

    return result;
}

char *bin_uint64_to_string(uint64_t value) {
    printf("Value: %llu\n", value);
    char *result = malloc(65);
    result[64] = '\0';
    for (int i = 63; i >= 0; i--) {
        if (value & (1 << i)) {
            result[63 - i] = '1';
        } else {
            result[63 - i] = '0';
        }
        printf("Result: %s\n", result);
    }

    printf("Result: %s\n", result);
    return result;
}

#endif  // BIN_IMPLEMENTATION

#endif  // BIN_H
