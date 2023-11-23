#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"

const uint ONBOARD_LED_PIN = 25;

const uint CAN_RX_LED_PIN_1 = 16;
const uint CAN_RX_LED_PIN_2 = 17;

const uint CAN_TX_LED_PIN_1 = 14;
const uint CAN_TX_LED_PIN_2 = 15;

bool toggle_rx = false;
bool toggle_tx = false;

static struct can2040 cbus;

static void can2040_cb(struct can2040 *bus, uint32_t notify, struct can2040_msg *msg) {
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
    can2040_pio_irq_handler(&cbus);
}

void can_setup() {
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000;
    uint32_t bitrate = 500000;

    uint32_t gpio_rx = 4;
    uint32_t gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
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

    can_setup();

    while (true) {
        gpio_put(ONBOARD_LED_PIN, true);

        struct can2040_msg *msg = &(struct can2040_msg){
            .id = 0x124,
            .dlc = 8,
            .data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06}};

        can2040_transmit(&cbus, msg);

        sleep_ms(1000);
        gpio_put(ONBOARD_LED_PIN, false);
        sleep_ms(1000);
    }
}
