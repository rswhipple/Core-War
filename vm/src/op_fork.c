#include "../include/op.h"

/* Takes 1 parameter, an index. Creates a new program, inheriting states
from the parent, and starting execution at Counter + parameter % IDX_MOD */

int inst_fork(core_t *core, cursor_t* cursor) 
{
    // Placeholder value holding the value of *inst
    // int *reg_index = inst;
    // //check if the index is valid
    // if (*reg_index< 0 || *reg_index >= REG_NUMBER)
    // {
    //     return 1; 
    // }

    // //calculate new counter for the child program
    // int new_counter = (champion->ac + champion->reg[*reg_index] % IDX_MOD + MEM_SIZE) % MEM_SIZE; //regs - array of registers

    // champion_t *child = (champion_t *)malloc(sizeof(champion_t));

    // *child = *champion;
    // child->ac = new_counter;

    return 0; // Success
}
