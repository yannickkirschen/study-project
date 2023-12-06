#ifndef MINI_RAIL_DECODER_H
#define MINI_RAIL_DECODER_H

#include <stdint.h>

#define MINI_RAIL_DECODER_STATE_STARTUP 0
#define MINI_RAIL_DECODER_STATE_READY 1
#define MINI_RAIL_DECODER_STATE_INIT 2
#define MINI_RAIL_DECODER_STATE_INIT_TRIGGER 3
#define MINI_RAIL_DECODER_STATE_RUNNING 4

typedef struct {
    uint32_t id;
    uint32_t state;
} mini_rail_decoder_t;

void mini_rail_decoder_init(mini_rail_decoder_t *decoder);

#ifdef MINI_RAIL_DECODER_IMPLEMENTATION

void mini_rail_decoder_init(mini_rail_decoder_t *decoder) {
    decoder->id = 0;
    decoder->state = MINI_RAIL_DECODER_STATE_STARTUP;
}

#endif  // MINI_RAIL_DECODER_IMPLEMENTATION

#endif  // MINI_RAIL_DECODER_H
