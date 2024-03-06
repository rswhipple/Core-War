#ifndef OP_HELPER_H
#define OP_HELPER_H
#include "op.h"

// function prototypes
void update_cursor(core_t *core, cursor_t *cursor, int i);
void update_cycles(core_t *core, cursor_t *cursor);
void update_carry(cursor_t *cursor, int dest_reg);


#endif