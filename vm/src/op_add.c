#include "../include/game_ops.h"

/* Takes 3 parameters: 3 registers. Add the first to the second, and store
the result to the third. Modifies the carry. */

int inst_add(core_t *core, cursor_t* cursor) {
  // check args

  int r1 = get_reg(core, cursor, 2);
  int r2 = get_reg(core, cursor, 3);
  int r3 = get_reg(core, cursor, 4);

  printf("Testing get_reg in inst_add:\n\tr1 = %i\nr2 = %i\nr3 = %i\n", r1, r2, r3);
  cursor->reg[r3] = cursor->reg[r1] + cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, &cursor, 5);

  return 0;
}
