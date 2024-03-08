#include "../include/game_ops.h"

/* Takes 1 parameter, that must be an index. Jumps to this index if carry is
1. Else, does nothing, but still consume time.
Zjmp %23 -> if carry == 1, Counter + 23 % IDX_MOD to Counter */

int inst_zjmp(core_t *core, cursor_t* cursor) {
  if (cursor->carry == 1) {
    // jump to that index
    int dir = get_dir(core, cursor, 1);
    int new_index = cursor->ac + MOD(dir);
    update_cursor(core, cursor, new_index);
    return EXIT_SUCCESS;
  }

  update_cursor(core, cursor, 5);
  return EXIT_SUCCESS;
}