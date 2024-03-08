#include "../include/game_ops.h"

/* Takes 1 parameter, an index. Creates a new program, inheriting states
from the parent, and starting execution at Counter + parameter % IDX_MOD */

int inst_fork(core_t *core, cursor_t *cursor) 
{
    int dir = get_dir(core, cursor, 1);
    int new_program_index = cursor->ac + MOD(dir);

    champion_t *child = (champion_t *)malloc(sizeof(champion_t));

    // TODO add cloning logic
    
    update_cursor(core, cursor, 5);
    return 0; // Success
}
