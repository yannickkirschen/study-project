#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION
#define BIN_IMPLEMENTATION

#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "rail/messaging.h"

#define CAN_RX_PIN      0
#define CAN_TX_PIN      1

#define ONBOARD_LED_PIN 25

static bool toggle = true;

typedef struct {
    uint32_t id;
    uint8_t gpio_red;
    uint8_t gpio_green;
} signal_t;

typedef struct {
    signal_t *signals;
} signals_t;

signal_t *signal_find_signal(signals_t *signals, uint32_t id);
void signal_receive_command(uint32_t signal_id, uint64_t data, error_t *error);
void signal_response_command(uint32_t signal_id, error_t *error);

static bool running = true;
static can2040_t can;
static signals_t all_signals;

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

static void signal_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
    if (notify & CAN2040_NOTIFY_RX) {
        gpio_put(ONBOARD_LED_PIN, toggle);
        toggle = !toggle;

        error_t *error = malloc(sizeof(error_t));
        error_init(error);

        switch (msg->id) {
        case MINI_RAIL_MESSAGE_COMMAND: {
            uint32_t id = can_get_element_id(msg, error);
            if (!error_has_error(error)) {
                signal_receive_command(id, can_get_element_data(msg), error);
            }

            signal_response_command(id, error);
            break;
        }
        case MINI_RAIL_MESSAGE_SHUTDOWN:
            running = false;
        default:
            break;
        }
    } else if (notify & CAN2040_NOTIFY_TX) {
        // Do something with the transmitted message.
    }
}

int main() {
    signal_t *signal1 = malloc(sizeof(signal_t));
    signal1->id = 0x01;
    signal1->gpio_red = 28;
    signal1->gpio_green = 27;

    arrput(all_signals.signals, *signal1);

    for (int i = 0; i < arrlen(all_signals.signals); i++) {
        gpio_init(all_signals.signals[i].gpio_red);
        gpio_set_dir(all_signals.signals[i].gpio_red, GPIO_OUT);
        gpio_put(all_signals.signals[i].gpio_red, 1);

        gpio_init(all_signals.signals[i].gpio_green);
        gpio_set_dir(all_signals.signals[i].gpio_green, GPIO_OUT);
    }

    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);

    can_setup(&can, PIOx_IRQHandler, signal_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    while (running) {
        // No-Op.
    }
}

signal_t *signal_find_signal(signals_t *signals, uint32_t id) {
    if (signals->signals == NULL) {
        return NULL;
    }

    for (int i = 0; i < arrlen(signals->signals); i++) {
        if (signals->signals[i].id == id) {
            return &signals->signals[i];
        }
    }

    return NULL;
}

void signal_receive_command(uint32_t signal_id, uint64_t data, error_t *error) {
    signal_t *signal = signal_find_signal(&all_signals, signal_id);
    if (signal == NULL) {
        error_add(error, MINI_RAIL_MESSAGING_ERROR_ELEMENT_NOT_FOUND, "The signal with the given ID was not found.");
        return;
    }

    if (data != 0 && data != 1) {
        error_add(error, MINI_RAIL_MESSAGING_ERROR_INVALID_DATA, "Signal indication unknown");
        return;
    }

    if (data == 0) {
        gpio_put(signal->gpio_red, 1);
        gpio_put(signal->gpio_green, 0);
    } else {
        gpio_put(signal->gpio_red, 0);
        gpio_put(signal->gpio_green, 1);
    }
}

void signal_response_command(uint32_t signal_id, error_t *error) {
    can2040_msg_t *response = malloc(sizeof(can2040_msg_t));
    if (error_has_error(error)) {
        can_create_message_from_int(response, MINI_RAIL_MESSAGE_RESPONSE_CODE, error->codes[0]);
    } else {
        can_create_message_from_int(response, MINI_RAIL_MESSAGE_RESPONSE_CODE, signal_id);
    }

    can2040_transmit(&can, response);
}
