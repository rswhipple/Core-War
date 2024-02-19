#ifndef MEMORY_H
#define MEMORY_H
#include "asm.h"

// function prototypes
t_header *init_header(void);
t_array *init_t_array(int size);
char *init_str(int size);

#endif