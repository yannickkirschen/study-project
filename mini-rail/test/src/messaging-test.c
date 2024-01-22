#include <stdint.h>
#include <stdio.h>

void print_bin(uint32_t n) {
    for (int i = 31, j = 0; i >= 0; i--, j++) {
        if (j == 8) {
            printf(" ");
            j = 0;
        }

        if (n & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }

    printf(" (%i)\n", n);
}

int main() {
    uint8_t data[8] = {1, 1, 0x34};

    uint32_t upper = data[0] << 12;
    uint32_t middle = data[1] << 4;
    uint32_t lower = (data[2] & 0xF0) >> 4;

    printf("data[0]: ");
    print_bin(upper);
    printf("data[1]: ");
    print_bin(middle);
    printf("data[2]: ");
    print_bin(lower);

    printf("all:     ");
    print_bin(upper | middle | lower);
}
