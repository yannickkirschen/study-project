#define MINI_RAIL_CONTROLLER_IMPLEMENTATION
#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include "rail/controller.h"
#include "rail/messaging.h"

#define CAN_RX_PIN 0
#define CAN_TX_PIN 1
#define BUTTON_PIN 2

static mini_rail_controller_t *controller;
static can2040_t can;

static void dummy_controller_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
}

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

int main() {
    controller = malloc(sizeof(mini_rail_controller_t));
    mini_rail_controller_init(controller);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    can_setup(&can, PIOx_IRQHandler, dummy_controller_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    bool button_was_high = false;
    controller->state = MINI_RAIL_CONTROLLER_STATE_READY;

    while (true) {
        if (gpio_get(BUTTON_PIN) && !button_was_high && controller->state == MINI_RAIL_CONTROLLER_STATE_READY) {
            button_was_high = true;
            controller->state = MINI_RAIL_CONTROLLER_STATE_INIT;

            can2040_msg_t *msg = &(can2040_msg_t){.id = 0, .dlc = 1, .data = {0x01}};
            can2040_transmit(&can, msg);
        } else if ((!gpio_get(BUTTON_PIN) && button_was_high) || !gpio_get(BUTTON_PIN)) {
            button_was_high = false;
        }

        sleep_ms(100);
    }
}
