#ifndef _OP_H_
#define _OP_H_
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MEM_SIZE (6 * 1024)
#define IDX_MOD 512
#define MAX_ARGS_NUMBER 4

#define MODA(x)	(x % MEM_SIZE < 0 ? x % MEM_SIZE + MEM_SIZE : x % MEM_SIZE)
#define MODAI(x)	(x % MEM_SIZE)
#define MODX(x)	(x % IDX_MOD)
#define MASKFF(x)	(x & 0xFF)
#define ABS(value)  (value > 0 ? value : -value)

#define RRR 0b01010100
#define RIR 0b01110100
#define RDR 0b01100100
#define IRR 0b11010100
#define IIR 0b11110100
#define IDR 0b11100100
#define DRR 0b10010100
#define DIR 0b10110100
#define DDR 0b10100100

#define COMMENT_CHAR '#'
#define LABEL_CHAR ':'
#define DIRECT_CHAR '%'
#define SEPARATOR_CHAR ','

#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"

/*r1 <-->rx*/
#define REG_NUMBER 16

/* live */

#define MAX_CHAMPIONS 4
#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 5
#define NBR_LIVE 40

/* buffer for getline */
#define BUF_SIZE 512

typedef char args_type_t;
typedef unsigned char code_t;
typedef struct champion_s champion_t;
typedef struct core_s core_t;

enum parameter_types {
  T_REG = 1,
  T_DIR = 2,
  T_IND = 4,
};

enum inst_elems {
  OPCODE,
  PARAM_DESC,
  VALUE_1,
  VALUE_2,
  VALUE_3,
};

// typedef struct inst_s {
//   int opcode;
//   int param_desc;
//   int value_1;
//   int value_2;
//   int value_3;
// } inst_t;

typedef struct op_s {
  char *mnemonique;
  char nbr_args;
  args_type_t type[MAX_ARGS_NUMBER];
  char code;
  int nbr_cycles;
  int (*inst)(champion_t *, core_t *, code_t, int *);
} op_t;

enum op_types {
  OP_LIVE = 1,
  OP_LD,
  OP_ST,
  OP_ADD,
  OP_SUB,
  OP_AND,
  OP_OR,
  OP_XOR,
  OP_ZJMP,
  OP_LDI,
  OP_STI,
  OP_FORK,
  OP_LLD,
  OP_LLDI,
  OP_LFORK,
  OP_AFF,
  OP_NOTHING,
  OP_NB,
};

/* size (in bytes) */
#define IND_SIZE 2
#define DIR_SIZE 4
#define REG_SIZE DIR_SIZE 

/* op_tab */
extern const op_t op_tab[];

/* HEADER */
#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct header_s {
  int     magic;
  char  prog_name[PROG_NAME_LENGTH + 1];
  int     prog_size;
  char  comment[COMMENT_LENGTH + 1];
} header_t;

typedef struct cursor_s
{
  struct cursor_s *next;
  bool        dead;                 // life status
  int     id;                       // id of champ
  int     carry;                    // carry flag
  int     index_start;              // starting core index
  int     ac;                       // counter (cursor)
  int     num_inst;                 // number of instructions
  int     current_inst;
  int     cycle;
  int     reg[REG_NUMBER];          // registers

} cursor_t;

struct champion_s
{
  char  *name;
  char  *comment;
  char  *string;
  int     string_len;
  int     id;                       // id of champ
  cursor_t *cursor;
  struct champion_s *next;            // next champion
};

struct core_s
{
  char memory[MEM_SIZE];            // the arena
  champion_t *champions;
  cursor_t *cursors;
  int     num_champions;            // number of champions
  int     cycle_to_die;             // number of cycles before being declared dead
  int     cycle_delta;              // number of cycles to decrement cycle_to_die by
  int     nbr_live;                 // number of live instructions before cycle_to_die is decremented by cycle_delta
  int     dump;                     // number of cycles before dumping memory
  int     cycle;                    // current cycle
  op_t op_tab[17];
};


int inst_live(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_ld(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_st(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_add(champion_t *champ, core_t *core, code_t code, int *args);
int inst_sub(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_and(champion_t *champ, core_t *core, code_t code, int *args);
int inst_or(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_xor(champion_t *champ, core_t *core, code_t code, int *args);
int inst_zjmp(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_ldi(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_sti(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_fork(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_lld(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_lldi(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_lfork(champion_t *champ, core_t *core, code_t code, int *inst);
int inst_aff(champion_t *champ, core_t *core, code_t code, int *inst);
void update_carry(champion_t *champ, int dest_reg);

#endif