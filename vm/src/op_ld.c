#include "../include/game_ops.h"

/* Takes 2 parameters: loads the first parameter to the second parameter.
Second parameter is a register. Ex: ld 34, r3 loads the REG_SIZE bytes
starting from the Counter + 34 % IDX_MOD into r3. */

int inst_ld(core_t *core, cursor_t* cursor) {

  update_cursor(core, cursor, 5);
  return 0;
}

int inst_ld_dir(core_t *core, cursor_t* cursor) {
  
  update_cursor(core, cursor, 7);
  return 0;
}