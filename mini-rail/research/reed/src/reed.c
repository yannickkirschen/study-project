#include <stdbool.h>

#include "pico/stdlib.h"

const uint ONBOARD_LED_PIN = 25;
const uint REED_1_PIN = 13;

void init_sign();

void callback(uint gpio, uint32_t event);

int main() {
    gpio_init(ONBOARD_LED_PIN);
    gpio_init(REED_1_PIN);

    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_set_dir(REED_1_PIN, GPIO_IN);

    gpio_set_irq_enabled_with_callback(REED_1_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);

    init_sign();
    while (true) {
    }
}

void callback(uint gpio, uint32_t event) {
    if (event == GPIO_IRQ_EDGE_RISE) {
        gpio_put(ONBOARD_LED_PIN, true);
    } else {
        gpio_put(ONBOARD_LED_PIN, false);
    }
}

void init_sign() {
    for (int i = 0; i < 3; i++) {
        gpio_put(ONBOARD_LED_PIN, true);
        sleep_ms(50);
        gpio_put(ONBOARD_LED_PIN, false);
        sleep_ms(50);
    }
}
