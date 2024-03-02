#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "rail/messaging.h"

const uint ONBOARD_LED_PIN = 25;

const uint CAN_RX_LED_PIN_1 = 16;
const uint CAN_RX_LED_PIN_2 = 17;

const uint CAN_TX_LED_PIN_1 = 15;
const uint CAN_TX_LED_PIN_2 = 14;

bool toggle_rx = false;
bool toggle_tx = false;

#define CAN_RX_PIN 0
#define CAN_TX_PIN 1

static can2040_t can;

static void slave_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
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

    can_setup(&can, PIOx_IRQHandler, slave_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    int interval = 1000;
    while (true) {
        gpio_put(ONBOARD_LED_PIN, true);

        can2040_msg_t *msg = &(can2040_msg_t){
            .id = 0x124,
            .dlc = 8,
            .data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};

        int rc = can2040_transmit(&can, msg);
        if (rc != 0) {
            interval = 100;
        }

        sleep_ms(interval);
        gpio_put(ONBOARD_LED_PIN, false);
        sleep_ms(interval);
    }
}
