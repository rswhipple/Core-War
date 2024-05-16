#include "../include/game_ops.h"

/* Takes 2 parameters: loads the first parameter to the second parameter.
Second parameter is a register. Ex: ld 34, r3 loads the REG_SIZE bytes
starting from the Counter + 34 % IDX_MOD into r3. */
int inst_ld_dr(core_t *core, cursor_t* cursor);

int inst_ld(core_t *core, cursor_t* cursor) {
u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  if (param_desc == DR) {
    inst_ld_dr(core, cursor);
  } else {
    int i = get_ind(core, cursor, 2);
    int r = get_reg(core, cursor, 4);

    cursor->reg[r] = MOD_IDX(i);
    update_cursor(core, cursor, 5);
  }
  return EXIT_SUCCESS;
}

int inst_ld_dr(core_t *core, cursor_t* cursor) {
  int d = get_dir(core, cursor, 2);
  int r = get_reg(core, cursor, 6);

  cursor->reg[r] = MOD_IDX(d);
  update_cursor(core, cursor, 7);
  return 0;
}