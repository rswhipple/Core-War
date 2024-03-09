#include "../include/game_loop.h"
#include "../include/game_ops.h"
#include "../include/print_tests.h"


int game_loop(core_t *core) {
    bool no_winner = true;
    cursor_t *cursor = core->cursors;

    printf("\n\n\n~~~###/// THE CORE WARS COMMENCE ///###~~~\n");
    while (no_winner) {
        if (cursor == core->cursors) {
            if (update_cycles(&core)) {
                return EXIT_SUCCESS;
            }
        }
        if (!cursor->dead) {
            if (cursor->running)
                add_run_cycle(cursor);
            else 
                execute_inst(core, cursor);
        }
        print_cursor(cursor);
        cursor = cursor->next;
    }

    return EXIT_SUCCESS;
}


int execute_inst(core_t *core, cursor_t *cursor) {
    int opcode = -1;
    opcode = command_to_opcode(core, cursor);
    if (opcode < 0) return 0; 

    const op_t *op = &op_tab[opcode]; 
    op->inst(core, cursor);

    printf("Champion \"%s\", #%i executed instruction #%i\n", 
                cursor->parent->name, cursor->parent->id, opcode + 1);

    return 1;
}

int	command_to_opcode(core_t *core, cursor_t *cursor) {
	unsigned char i;
    int opcode;

    i = (unsigned char)core->memory[cursor->ac]; 
    if (i >= 0x01 && i <= 0x0F) {
        opcode = ((int)i) - 1;
        return opcode;
    }
    else
        return 0;
}

