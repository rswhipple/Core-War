#ifndef TOKENIZE_H
#define TOKENIZE_H
#include "asm.h"

/* function prototypes */
t_array *tokenizer(char* param_1, char* param_2);
int number_of_toks(char* string, char* separator);
void parse_toks(char* param_1, char* param_2, t_array **tokens) ;

#endif

