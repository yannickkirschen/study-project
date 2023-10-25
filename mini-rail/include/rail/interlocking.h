#ifndef MINI_RAIL_INTERLOCKING_H
#define MINI_RAIL_INTERLOCKING_H

#include "rail/element.h"

typedef struct {
    mini_rail_element_t *elements;
    int element_count;
} mini_rail_interlocking_t;

#endif  // MINI_RAIL_INTERLOCKING_H
