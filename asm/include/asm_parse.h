#ifndef _ASM_PARSE_H_
#define _ASM_PARSE_H_
#include "asm.h"

// function prototypes
int execute_asm(char *filename);
FILE *create_cor_file(char *filename);
char *replace_ext(char *filename);
int read_file(FILE *fp, t_header **header, t_array **inst) ;
void print_usage();

#endif