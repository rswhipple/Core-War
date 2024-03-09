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

#define MOD(x)	(x % MEM_SIZE)
#define MOD_IDX(x)	(x % IDX_MOD)
#define MOD_AS(x)  (x % 256)
#define MASK_FF(x)	(x & 0xFF)

#define RRR 0b01010100
#define RIR 0b01110100
#define RDR 0b01100100
#define IRR 0b11010100
#define IIR 0b11110100
#define IDR 0b11100100
#define DRR 0b10010100
#define DIR 0b10110100
#define DDR 0b10100100
#define IR 0b11010000
#define DR 0b10010000

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
#define NBR_DUMP 40000

/* buffer for getline */
#define BUF_SIZE 512

typedef char args_type_t;
typedef unsigned char code_t;
typedef struct cursor_s cursor_t;
typedef struct champion_s champion_t;
typedef struct core_s core_t;

enum parameter_types 
{
  T_REG = 1,
  T_DIR = 2,
  T_IND = 4,
};

typedef struct op_s 
{
  char *mnemonique;
  char nbr_args;
  args_type_t type[MAX_ARGS_NUMBER];
  char code;
  int nbr_cycles;
  int (*inst)(core_t *, cursor_t *);
} op_t;

enum op_types 
{
  OP_LIVE,
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

typedef struct flag_s 
{
    int num_champions;
    int dump;
    int id;
    int address;
} flag_t;

typedef struct header_s 
{
  int     magic;
  char  prog_name[PROG_NAME_LENGTH + 1];
  int     prog_size;
  char  comment[COMMENT_LENGTH + 1];
} header_t;


struct cursor_s
{
  cursor_t *next;
  champion_t *parent;
  bool        dead;                 // life status
  bool        live;                 // was live called?
  int     carry;                    // carry flag
  int     index_start;              // starting core index
  int     ac;                       // counter (cursor)
  int     num_inst;                 // number of instructions
  int     current_inst;
  int     opcode;
  int     running;                  // keeps track of nbr cycles for current op   
  int     cycle;
  int     reg[REG_NUMBER];          // registers

};

struct champion_s
{
  char  *name;
  char  *comment;
  char  *string;
  int     string_len;
  int     id;                       // id of champ
  int     time_of_death;
  cursor_t *cursor;
  struct champion_s *next;            // next champion
};

struct core_s
{
  char memory[MEM_SIZE];            // the arena
  champion_t *champions;
  cursor_t *cursors;
  int     total_champs;            // number of champions
  int     cycle_to_die;             // number of cycles before being declared dead
  int     cycle_delta;              // number of cycles to decrement cycle_to_die by
  int     nbr_live;                 // number of live instructions before cycle_to_die is decremented by cycle_delta
  int     dump;                     // number of cycles before dumping memory
  int     cycle_count;              // current cycle in cycle to die
  int     live_count;               // number of cycle_to_die cycles
  unsigned int total_cycles;

  op_t op_tab[17];
};


int inst_live(core_t *core, cursor_t *cursor);
int inst_ld(core_t *core, cursor_t *cursor);
int inst_st(core_t *core, cursor_t *cursor);
int inst_add(core_t *core, cursor_t *cursor);
int inst_sub(core_t *core, cursor_t *cursor);
int inst_and(core_t *core, cursor_t *cursor);
int inst_or(core_t *core, cursor_t *cursor);
int inst_xor(core_t *core, cursor_t *cursor);
int inst_zjmp(core_t *core, cursor_t *cursor);
int inst_ldi(core_t *core, cursor_t *cursor);
int inst_sti(core_t *core, cursor_t *cursor);
int inst_fork(core_t *core, cursor_t *cursor);
int inst_lld(core_t *core, cursor_t *cursor);
int inst_lldi(core_t *core, cursor_t *cursor);
int inst_lfork(core_t *core, cursor_t *cursor);
int inst_aff(core_t *core, cursor_t *cursor);

#endif