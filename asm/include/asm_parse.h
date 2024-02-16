#ifndef _ASM_PARSE_H_
#define _ASM_PARSE_H_
#include "asm.h"

// function prototypes
int execute_asm(char *filename);
FILE *create_cor_file(char *filename);
int read_file(FILE *fp);
void print_usage();

#endif