#ifndef _OP_H_
#define _OP_H_
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MEM_SIZE (6 * 1024)
/*modulo of the index*/
#define IDX_MOD 512
/*this may not be changed 2^*IND_SIZE*/
#define MAX_ARGS_NUMBER 4

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
/* number of cycles before being decleared dead */
#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 5
#define NBR_LIVE 40

typedef char args_type_t;
typedef unsigned char code_t;
typedef struct champion champion_t;
typedef struct core_s core_t;

enum parameter_types {
  T_REG = 1,
  T_DIR = 2,
  T_IND = 4,
  T_LAB = 8
};

/* registers */ 
enum registers {
    R1 = 1, R2, R3, R4, R5, R6, R7, R8,     // general purpose registers
    R9, R10, R11, R12, R13, R14,            // general purpose registers   
    RAC,                                    // program counter
    RCND,                                   // condition register handles carry flag
};

struct op_s {
  char *mnemonique;
  char nbr_args;
  args_type_t type[MAX_ARGS_NUMBER];
  char code;
  int nbr_cycles;
  int (*inst)(champion_t *, core_t *, int *);
};

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
typedef struct op_s op_t;

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
  int magic;
  char prog_name[PROG_NAME_LENGTH + 1];
  int prog_size;
  char comment[COMMENT_LENGTH + 1];
} header_t;

typedef struct champion
{
    header_t *champ_header;       // header
    int id;                       // id of the champ
    int num_instuctions;          // number of instructions
    op_t *instructions;           // instruction array
    int registers[16];            // address of registers
    int pc;                       // program counter
    int carry;                    // carry flag
    struct champion *next;        // next champion

    void (*free_champion)(struct champion *champ);
} champion_t;

typedef struct core_s
{
    size_t memory[MEM_SIZE];       // for storing champions
    champion_t *champions;    // head of champion linked list
    int num_champions;             // number of champions
    int cycle_to_die;              // number of cycles before being declared dead
    int cycle_delta;               // number of cycles to decrement cycle_to_die by
    int nbr_live;                  // number of live instructions before cycle_to_die is decremented by cycle_delta
    int dump;                      // number of cycles before dumping memory
    int cycle;                     // current cycle

    void (*load_champion)(struct core_s *core, champion_t *champ);
    void (*free_core)(struct core_s *core);
} core_t;

int inst_live(champion_t *champ, core_t *core, int *inst);
int inst_ld(champion_t *champ, core_t *core, int *inst);
int inst_st(champion_t *champ, core_t *core, int *inst);
int inst_add(champion_t *champ, core_t *core, int *inst);
int inst_sub(champion_t *champ, core_t *core, int *inst);
int inst_and(champion_t *champ, core_t *core, int *inst);
int inst_or(champion_t *champ, core_t *core, int *inst);
int inst_xor(champion_t *champ, core_t *core, int *inst);
int inst_zjmp(champion_t *champ, core_t *core, int *inst);
int inst_ldi(champion_t *champ, core_t *core, int *inst);
int inst_sti(champion_t *champ, core_t *core, int *inst);
int inst_fork(champion_t *champ, core_t *core, int *inst);
int inst_lld(champion_t *champ, core_t *core, int *inst);
int inst_lldi(champion_t *champ, core_t *core, int *inst);
int inst_lfork(champion_t *champ, core_t *core, int *inst);
int inst_aff(champion_t *champ, core_t *core, int *inst);

#endif