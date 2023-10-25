#include <stdbool.h>

#include "pico/stdlib.h"

const uint ONBOARD_LED_PIN = 25;
const uint ERROR_UPPER_LED_PIN = 13;
const uint REED_1_PIN = 15;
const uint REED_2_PIN = 14;
const uint REED_3_PIN = 16;
const uint REED_4_PIN = 17;

void init_sign();

void callback(uint gpio, uint32_t event);

int main() {
    gpio_init(ONBOARD_LED_PIN);
    gpio_init(ERROR_UPPER_LED_PIN);
    gpio_init(REED_1_PIN);
    gpio_init(REED_2_PIN);
    gpio_init(REED_3_PIN);
    gpio_init(REED_4_PIN);

    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(REED_1_PIN, GPIO_IN);
    gpio_set_dir(REED_2_PIN, GPIO_IN);
    gpio_set_dir(REED_3_PIN, GPIO_IN);
    gpio_set_dir(REED_4_PIN, GPIO_IN);

    gpio_set_irq_enabled_with_callback(REED_1_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_2_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_3_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);
    gpio_set_irq_enabled_with_callback(REED_4_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &callback);

    init_sign();
    while (true) {
    }
}

void callback(uint gpio, uint32_t event_mask) {
    if (event_mask == GPIO_IRQ_EDGE_RISE) {
        switch (gpio) {
        case 15:
        case 14:
        case 16:
        case 17: {
            gpio_put(ONBOARD_LED_PIN, true);
            break;
        }
        default: {
            gpio_put(ERROR_UPPER_LED_PIN, true);
            break;
        }
        }
    } else if (event_mask == GPIO_IRQ_EDGE_FALL) {
        gpio_put(ONBOARD_LED_PIN, false);
        gpio_put(ERROR_UPPER_LED_PIN, false);
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
