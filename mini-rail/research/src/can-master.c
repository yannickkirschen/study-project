#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include "rail/messaging.h"

const uint ONBOARD_LED_PIN = 25;

const uint CAN_RX_LED_PIN_1 = 16;
const uint CAN_RX_LED_PIN_2 = 17;

const uint CAN_TX_LED_PIN_1 = 15;
const uint CAN_TX_LED_PIN_2 = 14;

const uint BUTTON_PIN = 0;

bool toggle_rx = false;
bool toggle_tx = false;

#define CAN_RX_PIN 0
#define CAN_TX_PIN 1
#define BUTTON_PIN 2

static can2040_t can;

static void master_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
    if (notify & CAN2040_NOTIFY_RX) {
        gpio_put(CAN_RX_LED_PIN_1, toggle_rx);
        gpio_put(CAN_RX_LED_PIN_2, !toggle_rx);
        toggle_rx = !toggle_rx;
    } else if (notify & CAN2040_NOTIFY_TX) {
        gpio_put(CAN_TX_LED_PIN_1, !toggle_tx);
        gpio_put(CAN_TX_LED_PIN_2, toggle_tx);
        toggle_tx = !toggle_tx;
    }
}

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

int main() {
    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);

    gpio_init(CAN_RX_LED_PIN_1);
    gpio_set_dir(CAN_RX_LED_PIN_1, GPIO_OUT);

    gpio_init(CAN_RX_LED_PIN_2);
    gpio_set_dir(CAN_RX_LED_PIN_2, GPIO_OUT);

    gpio_init(CAN_TX_LED_PIN_1);
    gpio_set_dir(CAN_TX_LED_PIN_1, GPIO_OUT);

    gpio_init(CAN_TX_LED_PIN_2);
    gpio_set_dir(CAN_TX_LED_PIN_2, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    can_setup(&can, PIOx_IRQHandler, master_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    bool button_was_high = false;

    while (true) {
        if (gpio_get(BUTTON_PIN) && !button_was_high) {
            button_was_high = true;

            can2040_msg_t *msg = &(can2040_msg_t){
                .id = 0x123,
                .dlc = 8,
                .data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};

            can2040_transmit(&can, msg);
        } else if ((!gpio_get(BUTTON_PIN) && button_was_high) || !gpio_get(BUTTON_PIN)) {
            button_was_high = false;
        }

        sleep_ms(100);
    }
}
