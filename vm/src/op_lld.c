#include "../include/game_ops.h"

/* Same as ld without the %IDX_MOD. Modifies the carry */

int inst_lld(core_t *core, cursor_t* cursor) {
  update_cursor(core, cursor, 5);
  return 0;
}

int inst_ldd_dir(core_t *core, cursor_t* cursor) {
  
  update_cursor(core, cursor, 7);
  return 0;
}