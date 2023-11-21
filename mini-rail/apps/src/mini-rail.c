#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#define clear_screen() clrscr()
#else
#define clear_screen() printf("\e[1;1H\e[2J")
#endif

#define STR_IMPLEMENTATION
#define GRAPH_IMPLEMENTATION
#define ERROR_IMPLEMENTATION
#define STB_DS_IMPLEMENTATION

#include "error.h"
#include "rail/database.h"
#include "rail/interlocking.h"
#include "str.h"

const char *RAIL_USAGE = "Usage: mini-rail [database]\n";

const char *RAIL_BANNER =
    "**** Welcome to MiniRail **** \n"
    "Press q to quit and h for help.\n\n";

typedef enum {
    RAIL_COMMAND_UNKNOWN = -1,
    RAIL_COMMAND_EXIT,
    RAIL_COMMAND_SET
} mini_rail_command_t;

typedef struct {
    mini_rail_interlocking_t *interlocking;
} mini_rail_state_t;

void rail_state_init(mini_rail_state_t *state);

void rail_state_init(mini_rail_state_t *state) {
    state->interlocking = NULL;
}

int rail_main(mini_rail_state_t *state);
mini_rail_command_t parse_command(mini_rail_state_t *state, char *command);
mini_rail_interlocking_t *rail_interlocking_load(error_t *error, char *filename);

mini_rail_command_t parse_command(mini_rail_state_t *state, char *command) {
    if (string_equals(command, "q")) {
        return RAIL_COMMAND_EXIT;
    } else if (string_starts_with(command, "set")) {
        return RAIL_COMMAND_SET;
    } else {
        return RAIL_COMMAND_UNKNOWN;
    }
}

mini_rail_interlocking_t *rail_interlocking_load(error_t *error, char *filename) {
    rail_database_t *database = malloc(sizeof(rail_database_t));
    rail_database_open(database, filename, error);
    if (error_has_error(error)) {
        return NULL;
    }

    mini_rail_interlocking_t *interlocking = malloc(sizeof(mini_rail_interlocking_t));
    rail_interlocking_init(interlocking);
    rail_database_interlocking_load(interlocking, database, error);
    if (error_has_error(error)) {
        return NULL;
    }

    return interlocking;
}

int rail_main(mini_rail_state_t *state) {
    char command[30];
    printf("\n> ");
    scanf("%s", command);

    mini_rail_command_t parsed_command = parse_command(state, command);
    switch (parsed_command) {
    case RAIL_COMMAND_EXIT:
        printf("Bye.\n");
        break;
    case RAIL_COMMAND_UNKNOWN:
    default: {
        char **tokens = NULL;
        string_split(command, '.', &tokens);

        int start_id = rail_interlocking_element_find(state->interlocking, tokens[0]);
        int end_id = rail_interlocking_element_find(state->interlocking, tokens[1]);

        error_t *error = malloc(sizeof(error_t));
        error_init(error);

        mini_rail_element_t *route = rail_interlocking_route_find_and_set(state->interlocking, start_id, end_id, error);
        if (error_has_error(error)) {
            error_print(error);
            break;
        }

        printf("Set route:\n");
        for (int i = 0; i < arrlen(route); i++) {
            mini_rail_element_t *element = &route[i];
            switch (element->type) {
            case RAIL_ELEMENT_SIGNAL:
                printf(" %s: %s\n", element->spec.signal->display_name, rail_signal_indication_string(element->spec.signal->indication));
                break;
            case RAIL_ELEMENT_SWITCH:
                printf(" %s: %s\n", element->spec._switch->display_name, rail_switch_position_string(element->spec._switch->position));
                break;
            case RAIL_ELEMENT_OPEN_TRACK:
                printf(" %s\n", element->spec.open_track->display_name);
                break;
            case RAIL_ELEMENT_NONE:
                break;
            }
        }
        return RAIL_COMMAND_SET;
    }
    }

    return parsed_command;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("%s", RAIL_USAGE);
        return -1;
    }

    clear_screen();
    printf("%s", RAIL_BANNER);

    char *filename = argv[1];
    printf("Loading database %s\n", filename);

    error_t *error = malloc(sizeof(error_t));
    error_init(error);
    mini_rail_interlocking_t *interlocking = rail_interlocking_load(error, filename);
    if (error_has_error(error)) {
        error_print(error);
        return -1;
    }

    mini_rail_state_t *state = malloc(sizeof(mini_rail_state_t));
    rail_state_init(state);
    state->interlocking = interlocking;

    int rc = RAIL_COMMAND_UNKNOWN;
    while (rc != RAIL_COMMAND_EXIT) {
        rc = rail_main(state);
    }

    return rc;
}
