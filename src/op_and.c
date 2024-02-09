#include "../include/op.h"

int inst_and(champion_t *champ, core_t *core, code_t code, int *args) {
  int operand_1_regs = args[VALUE_1];
  int operand_2_regs = args[VALUE_2];
  int dest_reg = args[VALUE_3];

  champ->reg[dest_reg] = champ->reg[operand_1_regs] & champ->reg[operand_2_regs];
  update_carry(champ, dest_reg);

  return 0;
}