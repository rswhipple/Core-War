#include "../include/game_ops.h"

/* Same as and and or, but performing an XOR. */
int inst_xor_rrr(core_t *core, cursor_t* cursor);
int inst_xor_rdr(core_t *core, cursor_t* cursor);
int inst_xor_rir(core_t *core, cursor_t* cursor);
int inst_xor_dir(core_t *core, cursor_t* cursor);
int inst_xor_ddr(core_t *core, cursor_t* cursor);
int inst_xor_iir(core_t *core, cursor_t* cursor);
int inst_xor_idr(core_t *core, cursor_t* cursor);


int inst_xor(core_t *core, cursor_t* cursor) {
  u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  switch (param_desc) {
    case RIR:
      inst_xor_rir(core, cursor);
      break;
    case RDR:
      inst_xor_rdr(core, cursor);
      break;
    case DDR:
      inst_xor_ddr(core, cursor);
      break;
    case DIR:
      inst_xor_dir(core, cursor);
      break;
    case IIR:
      inst_xor_iir(core, cursor);
      break;
    case IDR:
      inst_xor_idr(core, cursor);
      break;
    default:
      inst_xor_rrr(core, cursor);
      break;
  }

  return EXIT_SUCCESS;
}

int inst_xor_rrr(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac + 2];
  int r2 = (int)core->memory[cursor->ac + 3];
  int r3 = (int)core->memory[cursor->ac + 4];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 5);

  return EXIT_SUCCESS;
}

int inst_xor_rir(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac + 2];
  int r2 = get_ind(core, cursor, 3);
  int r3 = (int)core->memory[cursor->ac + 5];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 6);

  return EXIT_SUCCESS;
}


int inst_xor_rdr(core_t *core, cursor_t* cursor) {
  int r1 = (int)core->memory[cursor->ac + 2];
  int r2 = get_dir(core, cursor, 3);
  int r3 = (int)core->memory[cursor->ac + 7];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 8);

  return EXIT_SUCCESS;
}

int inst_xor_ddr(core_t *core, cursor_t* cursor) {
  int r1 = get_dir(core, cursor, 2);
  int r2 = get_dir(core, cursor, 6);
  int r3 = (int)core->memory[cursor->ac + 10];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 11);

  return EXIT_SUCCESS;
}

int inst_xor_dir(core_t *core, cursor_t* cursor) {
  int r1 = get_dir(core, cursor, 2);
  int r2 = get_ind(core, cursor, 6);
  int r3 = (int)core->memory[cursor->ac + 8];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 9);

  return EXIT_SUCCESS;
}

int inst_xor_iir(core_t *core, cursor_t* cursor) {
  int r1 = get_ind(core, cursor, 2);
  int r2 = get_ind(core, cursor, 4);
  int r3 = (int)core->memory[cursor->ac + 6];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 7);

  return EXIT_SUCCESS;
}

int inst_xor_idr(core_t *core, cursor_t* cursor) {
  int r1 = get_ind(core, cursor, 2);
  int r2 = get_dir(core, cursor, 4);
  int r3 = (int)core->memory[cursor->ac + 8];

  cursor->reg[r3] = cursor->reg[r1] ^ cursor->reg[r2];
  update_carry(cursor, r3);
  update_cursor(core, cursor, 9);

  return EXIT_SUCCESS;
}

