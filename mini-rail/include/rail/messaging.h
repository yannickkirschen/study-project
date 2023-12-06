#ifndef MINI_RAIL_MESSAGING_H
#define MINI_RAIL_MESSAGING_H

#include <stdint.h>

#include "RP2040.h"
#include "can2040.h"
#include "core_cm0plus.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "stb_ds_helper.h"

//
// Definition of the CAN message IDs for setup messages.
//

#define MINI_RAIL_MESSAGE_INIT_ENTER                  0x001  // Announce enter of init phase.
#define MINI_RAIL_MESSAGE_INIT_TRIGGER                0x002  // User pressed the hardware button.
#define MINI_RAIL_MESSAGE_INIT_CONTACT_POINT          0x003  // 20 bit for the contact point ID and 5 bit for the GPIO pin (2x).
#define MINI_RAIL_MESSAGE_INIT_CONTACT_POINT_DIRECTED 0x004  // 20 bit for the directed contact point ID, 20 bit for the first contact point ID and 20 bit for the second contact point ID.
#define MINI_RAIL_MESSAGE_INIT_CONTACT_COUNTER        0x005  // 20 bit for the contact counter ID and 20 bit for the directed contact point ID.
#define MINI_RAIL_MESSAGE_INIT_SIGNAL                 0x006  // 20 bit for the signal ID and 5 bits for the relay GPIO pin (2x).
#define MINI_RAIL_MESSAGE_INIT_SIGNAL_NO_RELAY        0x007  // 20 bit for the signal ID and 10 bits for the LED GPIO pins (2x).
#define MINI_RAIL_MESSAGE_INIT_SWITCH                 0x008  // TODO: how do we want to handle switches?
#define MINI_RAIL_MESSAGE_INIT_OK                     0x009  // Init phase is finished for decoder.
#define MINI_RAIL_MESSAGE_INIT_EXIT                   0x00A  // Announce that the init phase is done. Decoders now start working.

//
// Definition of the CAN message IDs for command messages.
//

#define MINI_RAIL_MESSAGE_COMMAND            0x101  // Set a signal or switch to specified indication/position.
#define MINI_RAIL_MESSAGE_GET_CURRENT_COUNT  0x111  // Request the current count of a given contact counter. 20 bits for the counter ID.
#define MINI_RAIL_MESSAGE_SET_TRACK_VACANT   0x112  // Instructs the vacancy detection to set a track section vacant. 20 bits for the counter ID.
#define MINI_RAIL_MESSAGE_SET_TRACK_OCCUPIED 0x113  // Instructs the vacancy detection to set a track section occupied. 20 bits for the counter ID and 12 bits for the count.
#define MINI_RAIL_MESSAGE_CHANGE_DIRECTION   0x114  // Instructs the vacancy detection to change the direction of a counter. 20 bits for the counter ID.
#define MINI_RAIL_MESSAGE_COUNTER_RESET      0x11F  // Instructs the vacancy detection to reset its counter. 20 bits for the counter ID.

//
// Definition of the CAN message IDs for vacancy detection responses.
//

#define MINI_RAIL_MESSAGE_TRACK_VACANT   0x201  // A track section has become vacant. 20 bit for the counter ID.
#define MINI_RAIL_MESSAGE_TRACK_OCCUPIED 0x202  // A track section has become occupied. 20 bit for the counter ID.
#define MINI_RAIL_MESSAGE_CURRENT_COUNT  0x203  // The current count of a given contact counter. 20 bits for the counter ID and 12 bits for the count.

//
// Definition of the CAN message IDs for general responses.
//

#define MINI_RAIL_MESSAGE_RESPONSE_CODE 0x30F  // Announce that a command has been executed successfully or could not be executed. 20 bit for the element ID and 8 bit for the response code.

//
// Definition of the response codes.
//

#define MINI_RAIL_RESPONSE_OK                                           0x00  // No error. 20 bit for the element ID.

#define MINI_RAIL_RESPONSE_SIGNAL_LED_BROKEN                            0x11  // A signal LED should turn on but does not. 20 bit for the signal ID.

#define MINI_RAIL_RESPONSE_SWITCH_NO_FINAL_POSITION                     0x21  // A switch could not be changed to final position. 20 bit for the switch ID.
#define MINI_RAIL_RESPONSE_SWITCH_OPENED                                0x22  // A switch has been driven open by a train. 20 bits for the switch ID.

#define MINI_RAIL_RESPONSE_VACANCY_ESCHEDE_ERROR                        0x31  // A train wants to leave a switch in two different directions. 20 bit for the counter ID.
#define MINI_RAIL_RESPONSE_VACANCY_TRAINS_APPROACH                      0x32  // Two trains approach each other on a single segment. 20 bit for the counter ID.
#define MINI_RAIL_RESPONSE_VACANCY_CHANGE_DIRECTION_VACANT              0x33  // There is no train in the section. 20 bit for the counter ID.
#define MINI_RAIL_RESPONSE_VACANCY_CHANGE_DIRECTION_NO_DIRECTION        0x34  // There is no direction to change to. 20 bit for the counter ID.
#define MINI_RAIL_RESPONSE_VACANCY_CHANGE_DIRECTION_MULTIPLE_DIRECTIONS 0x35  // There are multiple directions to change to (switch). 20 bit for the counter ID.

#define MINI_RAIL_RESPONSE_INTERNAL_ERROR                               0xFF  // An error that cannot be further specified.

//
// Definition of the CAN message IDs for shutdown.
//

#define MINI_RAIL_MESSAGE_SHUTDOWN 0x7FF  // Instructs the decoders to shut down.

typedef struct can2040 can2040_t;
typedef struct can2040_msg can2040_msg_t;

void can_setup(can2040_t *can, irq_handler_t handler, can2040_rx_cb callback, uint32_t rx, uint32_t tx);

#ifdef MINI_RAIL_MESSAGING_IMPLEMENTATION

void can_setup(can2040_t *can, irq_handler_t handler, can2040_rx_cb callback, uint32_t rx, uint32_t tx) {
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000;
    uint32_t bitrate = 500000;

    can2040_setup(can, pio_num);
    can2040_callback_config(can, callback);

    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, handler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    can2040_start(can, sys_clock, bitrate, rx, tx);
}

#endif  // MINI_RAIL_MESSAGING_IMPLEMENTATION

#endif  // MINI_RAIL_MESSAGING_H
