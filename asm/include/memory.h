#ifndef MEMORY_H
#define MEMORY_H
#include "asm.h"

// function prototypes
t_array *init_t_array(void);
char *init_str(int size);
void free_t_array(t_array *arr);

#endif