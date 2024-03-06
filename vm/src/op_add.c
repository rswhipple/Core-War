#include "../include/op.h"

// Adds the value stored in the first register to the second register's value and
// stores the result to the third register.
int inst_add(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac++];
  int r2 = (int)core->memory[cursor->ac++];
  int r3 = (int)core->memory[cursor->ac++];

  cursor->reg[r3] = cursor->reg[r1] + cursor->reg[r2];
  update_carry(cursor->parent, r3);

  return 0;
}