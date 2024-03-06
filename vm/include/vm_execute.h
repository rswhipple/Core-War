#ifndef _VM_EXECUTE_H_
#define _VM_EXECUTE_H_
#include "op.h"

// function prototypes
int game_loop(core_t *core);
void print_winner(core_t *core);
void check_for_winner(core_t **core, cursor_t **cursor, bool *no_winner);
int execute_inst(core_t *core, cursor_t *cursor);
int	command_to_opcode(core_t *core, cursor_t *cursor);

#endif