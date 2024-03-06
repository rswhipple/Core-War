#include "../include/op.h"

/* Takes 1 parameter, that must be an index. Jumps to this index if carry is
1. Else, does nothing, but still consume time.
Zjmp %23 -> if carry == 1, Counter + 23 % IDX_MOD to Counter */

int inst_zjmp(core_t *core, cursor_t* cursor) {
  return 0;
}