#include "../include/op_helper.h"

/* Same as fork without the %IDX_MOD. */

int inst_lfork(core_t *core, cursor_t* cursor) 
{
    //check if the index is valid
    // if (*reg_index< 0 || *reg_index >= REG_NUMBER)
    // {
    //     return 1; 
    // }

    // //calculate new counter for the child program
    // int new_counter = (champion->ac + champion->reg[*reg_index]) % MEM_SIZE; //regs - array of registers //we dont account for extra mem_size because there is no idx_mod

    // champion_t *child = (champion_t *)malloc(sizeof(champion_t));

    // *child = *champion;
    // child->ac = new_counter;

    return 0; // Success
}
