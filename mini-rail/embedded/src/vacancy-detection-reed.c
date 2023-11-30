#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#define MINI_RAIL_DECODER_IMPLEMENTATION
#define MINI_RAIL_MESSAGING_IMPLEMENTATION

#include <stdbool.h>
#include <stdlib.h>

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "rail/decoder.h"
#include "rail/messaging.h"
#include "rail/vacancy.h"

const uint ONBOARD_LED_PIN = 25;

const uint ERROR_UPPER_LED_PIN = 22;
const uint ERROR_MIDDLE_LED_PIN = 21;
const uint ERROR_LOWER_LED_PIN = 20;

const uint OCCUPIED_UPPER_LED_PIN = 13;
const uint OCCUPIED_MIDDLE_LED_PIN = 14;
const uint OCCUPIED_LOWER_LED_PIN = 15;

#define CAN_RX_PIN 0
#define CAN_TX_PIN 1
#define BUTTON_PIN 2

static mini_rail_decoder_t *decoder;
static can2040_t can;

bool toggle = false;

static void vacancy_detection_can_callback(can2040_t *bus, uint32_t notify, can2040_msg_t *msg) {
    if (notify & CAN2040_NOTIFY_RX) {
        gpio_put(ERROR_UPPER_LED_PIN, toggle);
        toggle = !toggle;

        switch (rail_message_decode_type(msg->id)) {
        case MINI_RAIL_MESSAGE_INIT_ENTER:
            decoder->state = MINI_RAIL_DECODER_STATE_INIT;
            break;
        case MINI_RAIL_MESSAGE_INIT_OK:
            decoder->state = MINI_RAIL_DECODER_STATE_RUNNING;
            decoder->id = rail_message_decode_receiver(msg->id);
            break;
        }
    } else if (notify & CAN2040_NOTIFY_TX) {
    }
}

static void PIOx_IRQHandler() {
    can2040_pio_irq_handler(&can);
}

void init_sign();

void show_three_bit_binary(int number, uint upper, uint middle, uint lower);

int main() {
    decoder = malloc(sizeof(mini_rail_decoder_t));
    mini_rail_decoder_init(decoder);

    gpio_init(ONBOARD_LED_PIN);
    gpio_init(ERROR_UPPER_LED_PIN);
    gpio_init(ERROR_MIDDLE_LED_PIN);
    gpio_init(ERROR_LOWER_LED_PIN);
    gpio_init(OCCUPIED_UPPER_LED_PIN);
    gpio_init(OCCUPIED_MIDDLE_LED_PIN);
    gpio_init(OCCUPIED_LOWER_LED_PIN);

    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_MIDDLE_LED_PIN, GPIO_OUT);
    gpio_set_dir(ERROR_LOWER_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_UPPER_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_MIDDLE_LED_PIN, GPIO_OUT);
    gpio_set_dir(OCCUPIED_LOWER_LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    decoder->state = MINI_RAIL_DECODER_STATE_READY;

    rail_contact_point_t *p1 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p2 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p3 = malloc(sizeof(rail_contact_point_t));
    rail_contact_point_t *p4 = malloc(sizeof(rail_contact_point_t));

    rail_contact_point_init(p1, 1);
    rail_contact_point_init(p2, 2);
    rail_contact_point_init(p3, 3);
    rail_contact_point_init(p4, 4);

    rail_contact_point_directed_t *d1 = malloc(sizeof(rail_contact_point_directed_t));
    rail_contact_point_directed_t *d2 = malloc(sizeof(rail_contact_point_directed_t));

    rail_contact_point_directed_init(d1, 1, p1, p2);
    rail_contact_point_directed_init(d2, 2, p4, p3);

    rail_contact_counter_t *c = malloc(sizeof(rail_contact_counter_t));
    rail_contact_counter_init(c, 1);

    rail_contact_counter_add_contact_point_directed(c, d1);
    rail_contact_counter_add_contact_point_directed(c, d2);

    rail_vacancy_t *v = malloc(sizeof(rail_vacancy_t));
    rail_vacancy_init(v);
    rail_vacancy_add_contact_counter(v, c);

    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    bool reed1_was_high = false;
    bool reed2_was_high = false;
    bool reed3_was_high = false;
    bool reed4_was_high = false;

    gpio_put(ONBOARD_LED_PIN, true);
    sleep_ms(1000);
    gpio_put(ONBOARD_LED_PIN, false);

    bool button_was_high = false;
    can_setup(&can, PIOx_IRQHandler, vacancy_detection_can_callback, CAN_RX_PIN, CAN_TX_PIN);

    while (true) {
        if (gpio_get(BUTTON_PIN) && !button_was_high && decoder->state == MINI_RAIL_DECODER_STATE_INIT) {
            button_was_high = true;
            decoder->state = MINI_RAIL_DECODER_STATE_INIT_TRIGGER;

            can2040_msg_t *msg = &(can2040_msg_t){.id = 0x3, .dlc = 0, .data = {0}};
            can2040_transmit(&can, msg);
        } else if ((!gpio_get(BUTTON_PIN) && button_was_high) || !gpio_get(BUTTON_PIN)) {
            button_was_high = false;
        }

        sleep_ms(100);

        //        bool reed1 = gpio_get(REED_1_PIN);
        //        bool reed2 = gpio_get(REED_2_PIN);
        //        bool reed3 = gpio_get(REED_3_PIN);
        //        bool reed4 = gpio_get(REED_4_PIN);
        //
        //        if (reed1 && !reed1_was_high) {
        //            reed1_was_high = true;
        //            rail_vacancy_trigger(v, p1, error);
        //        }
        //
        //        if (reed2 && !reed2_was_high) {
        //            reed2_was_high = true;
        //            rail_vacancy_trigger(v, p2, error);
        //        }
        //
        //        if (reed3 && !reed3_was_high) {
        //            reed3_was_high = true;
        //            rail_vacancy_trigger(v, p3, error);
        //        }
        //
        //        if (reed4 && !reed4_was_high) {
        //            reed4_was_high = true;
        //            rail_vacancy_trigger(v, p4, error);
        //        }
        //
        //        if (!reed1 && reed1_was_high) {
        //            reed1_was_high = false;
        //        }
        //
        //        if (!reed2 && reed2_was_high) {
        //            reed2_was_high = false;
        //        }
        //
        //        if (!reed3 && reed3_was_high) {
        //            reed3_was_high = false;
        //        }
        //
        //        if (!reed4 && reed4_was_high) {
        //            reed4_was_high = false;
        //        }
        //
        //        if (error_has_error(error)) {
        //            show_three_bit_binary(error->codes[0], ERROR_UPPER_LED_PIN, ERROR_MIDDLE_LED_PIN, ERROR_LOWER_LED_PIN);
        //        } else {
        //            gpio_put(ERROR_UPPER_LED_PIN, false);
        //            gpio_put(ERROR_MIDDLE_LED_PIN, false);
        //            gpio_put(ERROR_LOWER_LED_PIN, false);
        //        }
        //
        //        show_three_bit_binary(c->count, OCCUPIED_UPPER_LED_PIN, OCCUPIED_MIDDLE_LED_PIN, OCCUPIED_LOWER_LED_PIN);
        //
        //        sleep_ms(10);
    }
}

void show_three_bit_binary(int number, uint upper, uint middle, uint lower) {
    if (number == 0) {
        gpio_put(upper, false);
        gpio_put(middle, false);
        gpio_put(lower, false);
    } else if (number == 1) {
        gpio_put(upper, false);
        gpio_put(middle, false);
        gpio_put(lower, true);
    } else if (number == 2) {
        gpio_put(upper, false);
        gpio_put(middle, true);
        gpio_put(lower, false);
    } else if (number == 3) {
        gpio_put(upper, false);
        gpio_put(middle, true);
        gpio_put(lower, true);
    } else if (number == 4) {
        gpio_put(upper, true);
        gpio_put(middle, false);
        gpio_put(lower, false);
    } else if (number == 5) {
        gpio_put(upper, true);
        gpio_put(middle, false);
        gpio_put(lower, true);
    } else if (number == 6) {
        gpio_put(upper, true);
        gpio_put(middle, true);
        gpio_put(lower, false);
    } else if (number >= 7) {
        gpio_put(upper, true);
        gpio_put(middle, true);
        gpio_put(lower, true);
    }
}
