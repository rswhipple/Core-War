#ifndef MEMORY_H
#define MEMORY_H
#include "asm.h"

// function prototypes
t_header *init_header(void);
t_array *init_t_array(int size);
u_int8_t *init_int(int size);
t_node *init_node(int size);
t_arg *init_arg(void);
t_array *init_dict(void);
char *init_str(int size);
void free_dict(t_array *dict);
void free_t_array(t_array *tokens);
void free_nodes(t_node *head);
void free_t_arg(t_arg *arg);
void print_nodes(t_node *head);

#endif