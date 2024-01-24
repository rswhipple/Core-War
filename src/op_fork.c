#include "../include/op.h"

int inst_fork(champion_t *champion, core_t *core, int *reg_index) 
{
    //check if the index is valid
    if (*reg_index< 0 || *reg_index >= REG_NUMBER)
    {
        return 1; 
    }

    //calculate new counter for the child program
    int new_counter = (champion->counter + champion->regs[*reg_index] % IDX_MOD + MEM_SIZE) % MEM_SIZE; //regs - array of registers

    champion_t *child = (champion_t *)malloc(sizeof(champion_t));

    *child = *champion;
    child->counter = new_counter;

    return 0; // Success
}
