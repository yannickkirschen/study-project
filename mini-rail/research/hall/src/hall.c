#include "pico/binary_info.h"
#include "pico/stdlib.h"

const uint REED_1_PIN = 15;

int main() {
    gpio_init(REED_1_PIN);
    gpio_set_dir(REED_1_PIN, GPIO_OUT);

    while (true) {
        gpio_put(REED_1_PIN, 1);
        sleep_ms(250);
        gpio_put(REED_1_PIN, 0);
        sleep_ms(250);
    }
}
