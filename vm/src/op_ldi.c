#include "../include/game_ops.h"

/* Takes 3 parameters. First two are indexes and the third one is a register
Ex: ldi 3, %4, r1 -> reads IND_SIZ bytes from address Counter + 3 %
IDX_MOD, add 4 to this value (SumResult). REG_SIZE byte are read
from the Counter + SumResult % IDX_MOD and copies to r1. */

int inst_ldi_dr(core_t *core, cursor_t* cursor);

int inst_ldi(core_t *core, cursor_t* cursor) {
u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  if (param_desc == DR) {
    inst_ldi_dr(core, cursor);
  } else {
    int i = get_ind(core, cursor, 2);
    int r = get_reg(core, cursor, 4);

    cursor->reg[r] = MOD_IDX(i);
    update_cursor(core, cursor, 5);
  }
  return EXIT_SUCCESS;
}

int inst_ldi_dr(core_t *core, cursor_t* cursor) {
  int d = get_dir(core, cursor, 2);
  int r = get_reg(core, cursor, 6);

  cursor->reg[r] = MOD_IDX(d);
  update_cursor(core, cursor, 7);
  return 0;
}