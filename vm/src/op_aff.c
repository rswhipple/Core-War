#include "../include/op_helper.h"

/* Takes 1 parameter, a register. Displays to stdout the character
corresponding to the ASCII code of the content of the register (in base
10). A 256 modulo is applied to this ASCII code.
Ex; aff r3 -> outputs '*' if r3 contains 42. */

int inst_aff(core_t *core, cursor_t* cursor)
{
    // char c;

    // // Placeholder holding the value of num
    // int reg = *inst;

    // // check if the register is valid
    // if (reg < 0 || reg >= REG_NUMBER)
    // {
    //     return 1;
    // }

    // // get value from the register
    // int register_value = champion->reg[reg];

    // c = (char)(register_value % 256);
    // write(STDOUT_FILENO, &c, 1);

    return 0;
}
