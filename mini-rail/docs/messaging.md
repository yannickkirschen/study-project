# Messaging

MiniRail uses the CAN-Bus for messaging.

## Message format

As the CAN specification says, a data frame consists of an 11-bit identifier and
up to 8 bytes of data. The identifier is used to distinguish between different
messages. The data bytes are used to transport the actual message.

### Message types

There are the following message types:

| Identifier (bin)                | Identifier (hex) | Type                          | Sender     | Receiver     | Description                                                                                                                                 |
|---------------------------------|------------------|-------------------------------|------------|--------------|---------------------------------------------------------------------------------------------------------------------------------------------|
| **Setup**                       |                  |                               |            |              |                                                                                                                                             |
| `000 0000 0001`                 | `0x001`          | `INIT_ENTER`                  | Controller | All decoders | Announce enter of init phase.                                                                                                               |
| `000 0000 0010`                 | `0x002`          | `INIT_TRIGGER`                | Decoder    | Controller   | User pressed the hardware button.                                                                                                           |
| `000 0000 0011`                 | `0x003`          | `INIT_CONTACT_POINT`          | Controller | Decoder      | 20 bit for the contact point ID and 5 bit for the GPIO pin (2x).                                                                            |
| `000 0000 0100`                 | `0x004`          | `INIT_CONTACT_POINT_DIRECTED` | Controller | Decoder      | 20 bit for the directed contact point ID, 20 bit for the first contact point ID and 20 bit for the second contact point ID.                 |
| `000 0000 0101`                 | `0x005`          | `INIT_CONTACT_COUNTER`        | Controller | Decoder      | 20 bit for the contact counter ID and 20 bit for the directed contact point ID.                                                             |
| `000 0000 0110`                 | `0x006`          | `INIT_SIGNAL`                 | Controller | Decoder      | 20 bit for the signal ID and 5 bits for the relay GPIO pin (2x).                                                                            |
| `000 0000 0111`                 | `0x007`          | `INIT_SIGNAL_NO_RELAY`        | Controller | Decoder      | 20 bit for the signal ID and 10 bits for the LED GPIO pins (2x).                                                                            |
| `000 0000 1000`                 | `0x008`          | `INIT_SWITCH`                 | Controller | Decoder      |                                                                                                                                             |
| `000 0000 1001`                 | `0x009`          | `INIT_OK`                     | Controller | One decoder  | Init phase is finished for decoder.                                                                                                         |
| `000 0000 1010`                 | `0x00A`          | `INIT_EXIT`                   | Controller | All decoders | Announce that the init phase is done. Decoders now start working.                                                                           |
| **Commands**                    |                  |                               |            |              |                                                                                                                                             |
| `001 0000 0001`                 | `0x101`          | `COMMAND`                     | Controller | Decoder      | Set a signal or switch to specified indication/position.                                                                                    |
| `001 0001 0001`                 | `0x111`          | `GET_CURRENT_COUNT`           | Controller | Decoder      | Request the current count of a given contact counter. 20 bits for the counter ID.                                                           |
| `001 0001 0010`                 | `0x102`          | `SET_TRACK_VACANT`            | Controller | Decoder      | Instructs the vacancy detection to set a track section vacant. 20 bits for the counter ID.                                                  |
| `001 0001 0011`                 | `0x103`          | `SET_TRACK_OCCUPIED`          | Controller | Decoder      | Instructs the vacancy detection to set a track section occupied. 20 bits for the counter ID and 12 bits for the count.                      |
| `001 0001 0100`                 | `0x110`          | `CHANGE_DIRECTION`            | Controller | Decoder      | Instructs the vacancy detection to change the direction of a counter. 20 bits for the counter ID.                                           |
| `001 0001 1111`                 | `0x11F`          | `COUNTER_RESET`               | Controller | Decoder      | Instructs the vacancy detection to reset its counter. 20 bits for the counter ID.                                                           |
| **Vacancy detection responses** |                  |                               |            |              |                                                                                                                                             |
| `010 0000 0001`                 | `0x201`          | `TRACK_VACANT`                | Decoder    | Controller   | A track section has become vacant. 20 bit for the counter ID.                                                                               |
| `010 0000 0010`                 | `0x202`          | `TRACK_OCCUPIED`              | Decoder    | Controller   | A track section has become occupied. 20 bit for the counter ID.                                                                             |
| `010 0000 0011`                 | `0x203`          | `CURRENT_COUNT`               | Decoder    | Controller   | The current count of a given contact counter. 20 bits for the counter ID and 12 bits for the count.                                         |
| **General response**            |                  |                               |            |              |                                                                                                                                             |
| `011 0000 1111`                 | `0x30F`          | `RESPONSE_CODE`               | Decoder    | Controller   | Announce that a command has been executed successfully or could not be executed. 20 bit for the element ID and 8 bit for the response code. |
| **Shutdown**                    |                  |                               |            |              |                                                                                                                                             |
| `111 1111 1111`                 | `0x7FF`          | `SHUTDOWN`                    | Controller | All decoders | Instructs the decoders to shut down.                                                                                                        |

### Commands

| Data (bin)                      | Name         | Description                                                                                                       |
|---------------------------------|--------------|-------------------------------------------------------------------------------------------------------------------|
| `xxxx xxxx xxxx xxxx xxxx dddd` | `SET_SIGNAL` | Set a signal to a given indication, where `x` is the signal ID and `d` the indication (`0` = stop, `1` = clear).  |
| `xxxx xxxx xxxx xxxx xxxx 000d` | `SET_SWITCH` | Set a switch to a given position,  where `x` is the switch ID and `d` the position (`0` = base, `1` = alternate). |

### Response codes

| Code (bin)                   | Code (hex) | Name                                           | Description                                                                             |
|------------------------------|------------|------------------------------------------------|-----------------------------------------------------------------------------------------|
| **General response**         |            |                                                |                                                                                         |
| `0000 0000`                  | `0x00`     | `OK`                                           | No error. 20 bit for the element ID.                                                    |
| **Signal errors**            |            |                                                |                                                                                         |
| `0001 0001`                  | `0x11`     | `SIGNAL_LED_BROKEN`                            | A signal LED should turn on but does not. 20 bit for the signal ID.                     |
| **Switch errors**            |            |                                                |                                                                                         |
| `0010 0001`                  | `0x21`     | `SWITCH_NO_FINAL_POSITION`                     | A switch could not be changed to final position. 20 bit for the switch ID.              |
| `0010 0010`                  | `0x22`     | `SWITCH_OPENED`                                | A switch has been driven open by a train. 20 bits for the switch ID.                    |
| **Vacancy detection errors** |            |                                                |                                                                                         |
| `0011 0001`                  | `0x31`     | `VACANCY_ESCHEDE_ERROR`                        | A train wants to leave a switch in two different directions. 20 bit for the counter ID. |
| `0011 0010`                  | `0x32`     | `VACANCY_TRAINS_APPROACH`                      | Two trains approach each other on a single segment. 20 bit for the counter ID.          |
| `0011 0011`                  | `0x33`     | `VACANCY_CHANGE_DIRECTION_VACANT`              | There is no train in the section. 20 bit for the counter ID.                            |
| `0011 0100`                  | `0x34`     | `VACANCY_CHANGE_DIRECTION_NO_DIRECTION`        | There is no direction to change to. 20 bit for the counter ID.                          |
| `0011 0101`                  | `0x35`     | `VACANCY_CHANGE_DIRECTION_MULTIPLE_DIRECTIONS` | There are multiple directions to change to (switch). 20 bit for the counter ID.         |
| **General errors**           |            |                                                |                                                                                         |
| `1111 1111`                  | `0xFF`     | `INTERNAL_ERROR`                               |                                                                                         |
