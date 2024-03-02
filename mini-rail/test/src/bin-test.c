#define BIN_IMPLEMENTATION

#include "bin.h"

#include <stdio.h>

void assert(int expression) {
    if (!expression) {
        printf("Test failed\n");
        exit(1);
    } else {
        printf("Test passed\n");
    }
}

int main() {
    uint32_t a32 = bin_string_to_uint32("1011010001");
    printf("Test bin_string_to_uint32: ");
    assert(a32 == 721);

    char *b32 = bin_uint32_to_string(721);
    printf("Test bin_uint32_to_string: ");
    assert(strcmp(b32, "00000000000000000000001011010001") == 0);

    uint64_t a64 = bin_string_to_uint64("1011010001");
    printf("Test bin_string_to_uint64: ");
    assert(a64 == 721);

    //    char *b64 = bin_uint64_to_string(721);
    //    printf("Test bin_uint64_to_string: ");
    //    assert(strcmp(b64, "0000000000000000000000000000000000000000000000000000001011010001") == 0);

    bin_uint8_array_t *c = bin_string_to_uint8_array("000001000000000000010001");
    printf("Test bin_string_to_uint8_array: ");
    assert(c->data[0] == 0x04 && c->data[1] == 0x00 && c->data[2] == 0x11);

    uint8_t array[] = {0x04, 0x00, 0x11};
    char *s = bin_uint8_array_to_string(array, 4);
    printf("Test bin_uint8_array_to_string: ");
    assert(strcmp(s, "000001000000000000010001") == 0);
}
