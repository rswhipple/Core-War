#ifndef MEMORY_H
#define MEMORY_H
#include "asm.h"

// function prototypes
t_header *init_header(void);
t_array *init_t_array(void);
char *init_str(int size);
void free_t_array(t_array *arr);
void free_header(t_header *header);
#endif