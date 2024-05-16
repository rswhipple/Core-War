#include "../include/game_ops.h"

/* Takes 3 parameters. First two are indexes and the third one is a register
Ex: ldi 3, %4, r1 -> reads IND_SIZ bytes from address Counter + 3 %
IDX_MOD, add 4 to this value (SumResult). REG_SIZE byte are read
from the Counter + SumResult % IDX_MOD and copies to r1.  T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG */
int inst_ldi_rdr(core_t *core, cursor_t* cursor);
int inst_ldi_ddr(core_t *core, cursor_t* cursor);
int inst_ldi_idr(core_t *core, cursor_t* cursor);
int inst_ldi_irr(core_t *core, cursor_t* cursor);
int inst_ldi_drr(core_t *core, cursor_t* cursor);
int inst_ldi_rrr(core_t *core, cursor_t* cursor);

int inst_ldi(core_t *core, cursor_t* cursor) {
u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  switch (param_desc) {
    case RIR:
      inst_ldi_rdr(core, cursor);
      break;
    case RDR:
      inst_ldi_ddr(core, cursor);
      break;
    case DDR:
      inst_ldi_idr(core, cursor);
      break;
    case DIR:
      inst_ldi_irr(core, cursor);
      break;
    case IIR:
      inst_ldi_drr(core, cursor);
      break;
    default:
      inst_ldi_rrr(core, cursor);
      break;
  }

  return EXIT_SUCCESS;
}

int inst_ldi_rdr(core_t *core, cursor_t* cursor) {
  int r = get_reg_value(core, cursor, 2);
  int d = get_dir(core, cursor, 3);
  int r1 = get_reg(core, cursor, 7);

  int index = r + d;

  cursor->reg[r1] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 8);
  return 0;
}

int inst_ldi_ddr(core_t *core, cursor_t* cursor) {
  int d1 = get_dir(core, cursor, 2);
  int d2 = get_dir(core, cursor, 6);
  int r1 = get_reg(core, cursor, 11);

  int index = d1 + d2;

  cursor->reg[r1] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 12);
  return 0;
}

int inst_ldi_idr(core_t *core, cursor_t* cursor) {
  int i = get_ind(core, cursor, 2);
  int d = get_dir(core, cursor, 4);
  int r1 = get_reg(core, cursor, 8);

  int index = i + d;

  cursor->reg[r1] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 9);
  return 0;
}

int inst_ldi_irr(core_t *core, cursor_t* cursor) {
  int i = get_ind(core, cursor, 2);
  int r = get_reg_value(core, cursor, 4);
  int r1 = get_reg(core, cursor, 5);

  int index = i + r;

  cursor->reg[r1] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 6);
  return 0;
}

int inst_ldi_drr(core_t *core, cursor_t* cursor) {
  int d = get_dir(core, cursor, 2);
  int r = get_reg_value(core, cursor, 6);
  int r1 = get_reg(core, cursor, 7);

  int index = d + r;

  cursor->reg[r1] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 8);
  return 0;
}

int inst_ldi_rrr(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int r2 = get_reg_value(core, cursor, 3);
  int r3 = get_reg(core, cursor, 4);

  int index = r1 + r2;

  cursor->reg[r3] = MOD_IDX(get_bytes(core, cursor, index));
  
  update_cursor(core, cursor, 5);
  return 0;
}