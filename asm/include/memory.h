#ifndef MEMORY_H
#define MEMORY_H
#include "asm.h"

// function prototypes
t_header *init_header(void);
t_array *init_t_array(int size);
t_arg_array *init_arg_array(int size);
t_arg *init_arg(void);
t_array *init_dict(void);
char *init_str(int size);
void free_dict(t_array *dict);
void free_t_array(t_array *tokens);

#endif