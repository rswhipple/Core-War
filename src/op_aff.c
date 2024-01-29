#include "../include/op.h"
#include <unistd.h>

int inst_aff(champion_t *champion, core_t *core, int *inst)
{
    char c;

    // Placeholder holding the value of num
    int reg = *inst;

    // check if the register is valid
    if (reg < 0 || reg >= REG_NUMBER)
    {
        return 1;
    }

    // get value from the register
    int register_value = champion->registers[reg];

    c = (char)(register_value % 256);
    write(STDOUT_FILENO, &c, 1);

    return 0;
}
