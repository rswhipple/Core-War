#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "op.h"

// function prototypes
void cleanup(core_t *core);                         // frees all data
void free_champions(champion_t *champ);             // frees champions
char *init_str(int size);
char *init_and_strncpy(char *src);

#endif