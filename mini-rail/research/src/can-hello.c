#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include "rail/messaging.h"

#define CAN_RX_PIN 0
#define CAN_TX_PIN 1
#define BUTTON_PIN 2

static can2040_t can;

static void hello_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
}

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

int main() {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    can_setup(&can, PIOx_IRQHandler, hello_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    bool button_was_high = false;

    while (true) {
        if (gpio_get(BUTTON_PIN) && !button_was_high) {
            button_was_high = true;

            can2040_msg_t *msg = &(struct can2040_msg){.id = 0x799, .dlc = 2, .data = {0x03, 0x36}};
            int rc = can2040_transmit(&can, msg);
            if (rc != 0) {
                gpio_put(25, 1);
            } else {
                gpio_put(25, 0);
            }
        } else if ((!gpio_get(BUTTON_PIN) && button_was_high) || !gpio_get(BUTTON_PIN)) {
            button_was_high = false;
        }

        sleep_ms(100);
    }
}
