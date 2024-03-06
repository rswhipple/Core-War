#include "../include/op.h"

/* Takes 3 parameters: 3 registers. Add the first to the second, and store
the result to the third. Modifies the carry. */

int inst_add(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac++];
  int r2 = (int)core->memory[cursor->ac++];
  int r3 = (int)core->memory[cursor->ac++];

  cursor->reg[r3] = cursor->reg[r1] + cursor->reg[r2];
  update_carry(cursor->parent, r3);

  return 0;
}