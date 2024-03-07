#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_
#include "op.h"

// function prototypes
int game_loop(core_t *core);
int execute_inst(core_t *core, cursor_t *cursor);
int	command_to_opcode(core_t *core, cursor_t *cursor);

#endif