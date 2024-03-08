#include "../include/game_ops.h"

/* Same as ldi without the %IDX_MOD. Modifies the carry */

int inst_lldi(core_t *core, cursor_t* cursor) {
  update_cursor(core, cursor, 7);
  return 0;
}