#include "../include/game_ops.h"

/* Same as ld without the %IDX_MOD. Modifies the carry */
int inst_lld_dr(core_t *core, cursor_t* cursor);

int inst_lld(core_t *core, cursor_t* cursor) {
u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  if (param_desc == DR) {
    inst_lld_dr(core, cursor);
  } else {
    int i = get_ind(core, cursor, 2);
    int r = get_reg(core, cursor, 4);

    cursor->reg[r] = i;
    update_cursor(core, cursor, 5);
  }
  return EXIT_SUCCESS;
}

int inst_lld_dr(core_t *core, cursor_t* cursor) {
  int d = get_dir(core, cursor, 2);
  int r = get_reg(core, cursor, 6);

  cursor->reg[r] = d;
  update_cursor(core, cursor, 7);
  return 0;
}