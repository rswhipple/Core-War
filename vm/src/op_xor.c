#include "../include/game_ops.h"

/* Same as and and or, but performing an XOR. */

int inst_xor(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac + 2];
  int r2 = (int)core->memory[cursor->ac + 3];
  int r3 = get_reg(core, cursor, 3);

  printf("Testing get_reg in inst_xor:\n\tr1 = %i\nr2 = %i\nr3 = %i\n", r1, r2, r3);
  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 5);

  return 0;
}