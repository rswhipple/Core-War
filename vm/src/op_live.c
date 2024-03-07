#include "../include/op_helper.h"

/* Takes 1 parameter: 4 bytes that represent the player's number.
Indicates the player is alive. */

int inst_live(core_t *core, cursor_t* cursor) {
  int value_1;
  value_1 = get_dir(core, cursor, 1);
  char *live = printf("The program %i (%s) is alive.", value_1, cursor->parent->name);
  cursor->live = true;
  update_cursor(core, cursor, 3);
  return 0;
}