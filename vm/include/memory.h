#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "op.h"
// #include "vm_parse.h"
#include "helper.h"

// function prototypes
void cleanup(core_t *core);       // frees all data
void free_champions(champion_t *champ);             // frees champions
char *init_str(int size);
char *init_and_strncpy(char *src);
// inst_t *init_inst(void);
// inst_t **init_inst_array(int size);
// void free_core(core_t *core);                   // frees core

#endif