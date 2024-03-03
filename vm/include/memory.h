#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "op.h"
#include "vm_parse.h"

// function prototypes
void cleanup(champion_t *head, core_t *core);       // frees all data
void free_champions(champion_t *champ);             // frees champions
inst_t init_inst(void);
inst_array_t *init_inst_array(int size);
void free_inst_array(inst_array_t *array);
// void free_core(core_t *core);                   // frees core

#endif