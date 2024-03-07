#ifndef OP_HELPER_H
#define OP_HELPER_H
#include "op.h"

// function prototypes
void update_cursor(core_t *core, cursor_t *cursor, int i);
void update_carry(cursor_t *cursor, int dest_reg);

#endif