#include "../include/game_ops.h"

/* Same as fork without the %IDX_MOD. */

int inst_lfork(core_t *core, cursor_t* cursor) 
{
    int dir = get_dir(core, cursor, 1);
    int new_program_index = cursor->ac + dir;

    champion_t *child = (champion_t *)malloc(sizeof(champion_t));

    
    // child->ac = new_counter;
    update_cursor(core, cursor, 5);
    return 0; // Success
}
