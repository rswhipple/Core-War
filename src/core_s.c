#include "../include/op.h"

typedef struct champion
{
    header_t champ_header;                        // header
    char name[PROG_NAME_LENGTH + 1];              // name of the champ
    char comment[COMMENT_LENGTH + 1];             // comment of the champ
    int id;                                       // id of the champ
    instruction_t instructions[MAX_INSTRUCTIONS]; // instructiom
} champion_t;

typedef struct core_s
{
    t_byte memory[MEM_SIZE];           // for storing champions
    process_t champion[MAX_CHAMPIONS]; // champs processes/instructions
    int CYCLE_TO_DIE;
    int NBR_LIVE // cycle to live?

} core_t;