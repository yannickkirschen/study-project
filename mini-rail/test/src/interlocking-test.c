#define STR_IMPLEMENTATION
#define GRAPH_IMPLEMENTATION
#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#include "rail/interlocking.h"

#include "rail/database.h"
#include "stb_ds_helper.h"

int main() {
    //                         /- N2(4) - P2(6) -\
    // LEFT(9) - A(1) - SW1(7) -- N1(3) - P1(5) -- SW2(8) - F(2) - RIGHT(10)

    error_t *error = malloc(sizeof(error_t));
    error_init(error);

    rail_database_t *database = malloc(sizeof(rail_database_t));
    rail_database_open(database, "examples/simple-layout-1.sqlite", error);

    mini_rail_interlocking_t *interlocking = malloc(sizeof(mini_rail_interlocking_t));
    rail_interlocking_init(interlocking);
    rail_database_interlocking_load(interlocking, database, error);

    mini_rail_element_t *route = rail_interlocking_route_find_and_set(interlocking, 1, 6, error);
    error_print(error);
    rail_elements_print(route);

    return 0;
}
