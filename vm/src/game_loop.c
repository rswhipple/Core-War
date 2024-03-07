#include "../include/game_loop.h"


int game_loop(core_t *core) {
    bool no_winner = true;
    cursor_t *cursor = core->cursors;

    printf("\n\n\n~~~###/// THE CORE WARS COMMENCE ///###~~~\n");
    while (no_winner) {
        if (cursor == core->cursors) {
            if (update_cycles(&core)) {
                no_winner = false;
                break;
            }
        }
        if (!cursor->dead) {
            if (cursor->running) {
                // TODO add logic
            }
            printf("champion %s #%i\n", cursor->parent->name, cursor->parent->id);
            execute_inst(core, cursor);
        }
        cursor = cursor->next;
    }

    return EXIT_SUCCESS;
}

void check_for_winner(core_t **core, cursor_t **cursor, bool *no_winner) {
    (*cursor)->flag = false;
    (*core)->live_champs -= 1;
    if ((*core)->live_champs == 1) {
        *no_winner = false;
    }
}

void print_winner(core_t *core) {
    printf("--------------------------------------------\n");
    printf("\n\tA winner has been declared\n\n\n");
    printf("\nThe winner of the war over the cores is...\n\n\n");
    printf("\n\t%s\n\n", core->champions->name);
    printf("--------------------------------------------\n\n");
    printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
}


int execute_inst(core_t *core, cursor_t *cursor) {
    int opcode = command_to_opcode(core, cursor);
    if (!opcode) return 0;  // TODO add error message

    const op_t *op = &op_tab[opcode]; 
    op->inst(core, cursor);

    return 1;
}

int	command_to_opcode(core_t *core, cursor_t *cursor) {
	unsigned char i;
    int opcode;

    i = (unsigned char)core->memory[cursor->ac]; 
    if (i >= 0x01 && i <= 0x0F) {
        opcode = ((int)i) - 1;
        printf("opcode = %i\n", opcode);
        return opcode;
    }
    else
        return 0;
}

