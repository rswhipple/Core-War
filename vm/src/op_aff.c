#include "../include/game_ops.h"

/* Takes 1 parameter, a register. Displays to stdout the character
corresponding to the ASCII code of the content of the register (in base
10). A 256 modulo is applied to this ASCII code.
Ex; aff r3 -> outputs '*' if r3 contains 42. */

int inst_aff(core_t *core, cursor_t* cursor)
{
    char c;
    int r = get_reg(core, cursor, 3);

    if (r == -1) return EXIT_FAILURE;
    int reg_value = cursor->reg[r];

    c = (char)(reg_value % 256);
    write(STDOUT_FILENO, &c, 1);

    update_cursor(core, cursor, 2);

    return EXIT_SUCCESS;
}
