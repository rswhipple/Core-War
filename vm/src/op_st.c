#include "../include/game_ops.h"

/* Takes 2 parameters: Stores first parameter (a register) into the second
parameter (it can be another register or a number). Ex: st r4, 34 stores
r4 at the address of Counter + 34 % IDX_MOD; st r3, r8 copies r3 into
r8. */
int inst_st_ind(core_t *core, cursor_t* cursor);

int inst_st(core_t *core, cursor_t* cursor) {
  u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  if (param_desc == RI) {
    inst_st_ind(core, cursor);
  } else {
    int r1 = get_reg_value(core, cursor, 2);
    int r2 = get_reg(core, cursor, 4);

    cursor->reg[r2] = r1;
    update_cursor(core, cursor, 4);
  }

  return EXIT_SUCCESS;
}

int inst_st_ind(core_t *core, cursor_t* cursor) {
  int r = get_reg(core, cursor, 2);
  int i = get_ind(core, cursor, 3);

  cursor->reg[r] = MOD_IDX(core->memory[cursor->ac + i]); 
  update_cursor(core, cursor, 5);
  
  return EXIT_SUCCESS;
}