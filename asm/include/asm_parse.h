#ifndef _ASM_PARSE_H_
#define _ASM_PARSE_H_
#include "asm.h"

// function prototypes
int execute_asm(char *filename);
t_node *read_file(FILE *fp, t_header **header, t_prog_size *size); 
FILE *create_cor_file(char *filename);
char *replace_ext(char *filename);
void remove_line_title(char *dest, char *line, int size);
t_node *string_to_node(char *src, t_prog_size *size);
void token_to_arg(t_node **args, char *tok, int type);
void ttoa_remove_char(t_node **args, char *tok, int type);
bool is_special_command(char *command);

#endif