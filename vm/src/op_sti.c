#include "../include/game_ops.h"

/* Takes 3 parameters. The first one is a register. The other two can either
be indexes or registers. Ex: sti r2, %4, %5 -> copies the content for r2
into Counter + (4 + 5) % IDX_MOD. */

int inst_sti(core_t *core, cursor_t* cursor) {
  update_cursor(core, cursor, 11);
  return 0;
}