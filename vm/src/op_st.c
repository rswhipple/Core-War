#include "../include/game_ops.h"

/* Takes 2 parameters: Stores first parameter (a register) into the second
parameter (it can be another register or a number). Ex: st r4, 34 stores
r4 at the address of Counter + 34 % IDX_MOD; st r3, r8 copies r3 into
r8. */

int inst_st(core_t *core, cursor_t* cursor) {
  update_cursor(core, cursor, 4);
  return 0;
}

int inst_st_ind(core_t *core, cursor_t* cursor) {
  update_cursor(core, cursor, 5);
  return 0;
}