#include "../include/op.h"

int inst_or(champion_t *champ, core_t *core, code_t code, int *args) {
  int operand_1_reg = args[VALUE_1];
  int operand_2_reg = args[VALUE_2];
  int dest_reg = args[VALUE_3];

  champ->reg[dest_reg] = champ->reg[operand_1_reg] | champ->reg[operand_2_reg];
  update_carry(champ, dest_reg);

  return 0;
}