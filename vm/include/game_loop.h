#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_
#include "op.h"

// function prototypes
int game_loop(core_t *core);
void check_for_winner(core_t **core, cursor_t **cursor, bool *no_winner);
void print_winner(core_t *core);
int execute_inst(core_t *core, cursor_t *cursor);
void add_cycle(core_t **core);
int	command_to_opcode(core_t *core, cursor_t *cursor);

#endif