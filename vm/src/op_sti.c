#include "../include/game_ops.h"

/* Takes 3 parameters. The first one is a register. The other two can either
be indexes or registers. Ex: sti r2, %4, %5 -> copies the content for r2
into Counter + (4 + 5) % IDX_MOD. {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG} */
int inst_sti_rid(core_t *core, cursor_t* cursor);
int inst_sti_rdd(core_t *core, cursor_t* cursor);
int inst_sti_rir(core_t *core, cursor_t* cursor);
int inst_sti_rdr(core_t *core, cursor_t* cursor);
int inst_sti_rrd(core_t *core, cursor_t* cursor);
int inst_sti_rrr(core_t *core, cursor_t* cursor);

int inst_sti(core_t *core, cursor_t* cursor) {
  u_int8_t param_desc = (u_int8_t)core->memory[cursor->ac + 1];

  switch (param_desc) {
    case RID:
      inst_sti_rid(core, cursor);
      break;
    case RDD:
      inst_sti_rdd(core, cursor);
      break;
    case RIR:
      inst_sti_rir(core, cursor);
      break;
    case RDR:
      inst_sti_rdr(core, cursor);
      break;
    case RRD:
      inst_sti_rrd(core, cursor);
      break;
    default:
      inst_sti_rrr(core, cursor);
      break;
  }

  return EXIT_SUCCESS;
}


int inst_sti_rid(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int i = get_ind(core, cursor, 3);
  int d = get_dir(core, cursor, 5);

  core->memory[cursor->ac + MOD_IDX(i + d)] = r1;
  
  update_cursor(core, &cursor, 9);

  return EXIT_SUCCESS;
}

int inst_sti_rdd(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int d1 = get_dir(core, cursor, 3);
  int d2 = get_dir(core, cursor, 7);

  // printf("Testing in inst_sti:\n");
  // printf("r1 = %i, d1 = %i, d2 = %i\nMOD_IDX(d1 + d2) = %i\n",r1, d1, d2, MOD_IDX(d1 + d2));
  // printf("cursor->ac = %i\n", cursor->ac);
  core->memory[cursor->ac + MOD_IDX(d1 + d2)] = MASK_FF(r1 >> 24);
  
  update_cursor(core, &cursor, 11);

  return EXIT_SUCCESS;
}

int inst_sti_rir(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int i = get_ind(core, cursor, 3);
  int r2 = get_reg_value(core, cursor, 5);

  core->memory[cursor->ac + MOD_IDX(i + r2)] = r1;
  
  update_cursor(core, &cursor, 6);

  return EXIT_SUCCESS;
}

int inst_sti_rdr(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int d = get_dir(core, cursor, 3);
  int r2 = get_reg_value(core, cursor, 7);

  core->memory[cursor->ac + MOD_IDX(d + r2)] = r1;
  
  update_cursor(core, &cursor, 8);

  return EXIT_SUCCESS;
}

int inst_sti_rrd(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int r2 = get_reg_value(core, cursor, 3);
  int d = get_dir(core, cursor, 4);

  core->memory[cursor->ac + MOD_IDX(r2 + d)] = r1;
  
  update_cursor(core, &cursor, 8);

  return EXIT_SUCCESS;
}

int inst_sti_rrr(core_t *core, cursor_t* cursor) {
  int r1 = get_reg_value(core, cursor, 2);
  int r2 = get_reg_value(core, cursor, 3);
  int r3 = get_reg_value(core, cursor, 4);

  core->memory[cursor->ac + MOD_IDX(r2 + r3)] = r1;
  
  update_cursor(core, &cursor, 5);

  return EXIT_SUCCESS;
}