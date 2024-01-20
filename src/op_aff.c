#include "../include/op.h"

int inst_aff(champion_t *champion, core_t *core, int *reg)
{
    char c;

    // check if the register is valid
    if (*reg < 0 || *reg >= REG_NUMBER)
    {
        return 1;
    }

    // get value from the register
    int register_value = champion->regs[*reg]; //are we using regs array or something else? 

    c = (char)(register_value % 256);
    write(STDOUT_FILENO, &c, 1)

    return 0;
}
