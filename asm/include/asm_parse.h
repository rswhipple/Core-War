#ifndef _ASM_PARSE_H_
#define _ASM_PARSE_H_
#include "asm.h"

// function prototypes
int execute_asm(char *filename);
t_node *read_file(FILE *fp, t_header **header);
FILE *create_cor_file(char *filename);
char *replace_ext(char *filename);
void remove_line_title(t_header **header, char *line, int size);
t_node *string_to_node(char *src);
void token_to_arg(t_node **args, char *tok, int type);

#endif