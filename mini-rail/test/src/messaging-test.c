#include <stdint.h>
#include <stdio.h>

void print_bin_32(uint32_t n) {
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

    printf(" (%u)\n", n);
}

void print_bin_64(uint64_t n) {
    for (int i = 63, j = 0; i >= 0; i--, j++) {
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

    printf(" (%llu)\n", n);
}

uint64_t join_bytes(uint32_t argc, const uint32_t argv[]) {
    uint64_t result = 0;
    for (int i = 0; i < argc; i++) {
        uint64_t v = argv[i];
        print_bin_64(v);

        // Remove leading zero bits from v
        while ((v & 0x80000000) == 0) {
            v = v << 1;
        }

        //        print_bin_32(v);
        print_bin_64(v);

        //        uint64_t mask = 0x8000000000000000;
        //
        //        // Iterate through result, find the first zero bit and start writing v there
        //        while (mask != 0) {
        //            if ((mask & result) == 0) {
        //                print_bin_64(result);
        //                print_bin_64(v);
        //                result = result | v;
        //                break;
        //            }
        //
        //            mask = mask >> 1;
        //            v = v >> 1;
        //        }
    }

    return result;
}

int main() {
    uint8_t data[8] = {1, 1, 0x34};

    uint32_t upper = data[0] << 12;
    uint32_t middle = data[1] << 4;
    uint32_t lower = (data[2] & 0xF0) >> 4;

    printf("data[0]: ");
    print_bin_32(upper);
    printf("data[1]: ");
    print_bin_32(middle);
    printf("data[2]: ");
    print_bin_32(lower);

    printf("all:     ");
    print_bin_32(upper | middle | lower);

    printf("----------------------\n");

    uint32_t argc = 1;
    uint32_t argv[] = {0xFF, 0xAA};
    uint64_t result = join_bytes(argc, argv);

    //    for (int i = 0; i < argc; i++) {
    //        printf("argv[%d]: ", i);
    //        print_bin_32(argv[i]);
    //    }
    //
    //    printf("result:  ");
    //    print_bin_64(result);

    //    uint32_t a = 0xFF;
    //    uint64_t b = a;
    //
    //    printf("a: ");
    //    print_bin_32(a);
    //    printf("b: ");
    //    print_bin_64(b);
}
