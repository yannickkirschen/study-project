#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define STR_IMPLEMENTATION
#define BIN_IMPLEMENTATION

#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#define CAN_RX_PIN       2
#define CAN_TX_PIN       3
#define ONBOARD_LED_PIN  25
#define CAN_RX_LED_PIN_1 17
#define CAN_RX_LED_PIN_2 16

#define MAX_MESSAGE_SIZE 100

#include "pico/stdlib.h"
#include "rail/messaging.h"
#include "str.h"

static can2040_t can;
bool toggle_rx = false;

static void can_serial_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
    if (notify & CAN2040_NOTIFY_RX) {
        gpio_put(CAN_RX_LED_PIN_1, toggle_rx);
        gpio_put(CAN_RX_LED_PIN_2, !toggle_rx);
        toggle_rx = !toggle_rx;

        printf("Received from Bus: ");
        can_print_serial_string(msg);
    } else if (notify & CAN2040_NOTIFY_TX) {
        gpio_put(CAN_RX_LED_PIN_1, toggle_rx);
        gpio_put(CAN_RX_LED_PIN_2, !toggle_rx);
        toggle_rx = !toggle_rx;
    }
}

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

int main() {
    stdio_init_all();

    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);

    gpio_init(CAN_RX_LED_PIN_1);
    gpio_set_dir(CAN_RX_LED_PIN_1, GPIO_OUT);

    gpio_init(CAN_RX_LED_PIN_2);
    gpio_set_dir(CAN_RX_LED_PIN_2, GPIO_OUT);

    gpio_put(CAN_RX_LED_PIN_1, true);
    gpio_put(CAN_RX_LED_PIN_2, true);
    sleep_ms(500);
    gpio_put(CAN_RX_LED_PIN_1, false);
    gpio_put(CAN_RX_LED_PIN_2, false);

    can_setup(&can, PIOx_IRQHandler, can_serial_callback, CAN_RX_PIN, CAN_TX_PIN);

    while (true) {
        char buffer[MAX_MESSAGE_SIZE];
        fgets(buffer, MAX_MESSAGE_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        can2040_msg_t *msg = malloc(sizeof(can2040_msg_t));
        can_read_serial_string(msg, buffer);

        printf("Sending onto Bus: ");
        can_print_serial_string(msg);

        int rc = can2040_transmit(&can, msg);
        printf("Transmit status: %d\n", rc);
    }
}
