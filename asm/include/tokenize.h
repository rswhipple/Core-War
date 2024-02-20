#ifndef TOKENIZE_H
#define TOKENIZE_H
#include "asm.h"

/* function prototypes */
t_array *tokenizer(char* param_1, char* param_2);
int number_of_strings(char* string, char* separator);
char **array_substrings(char* param_1, char* param_2, int count);

#endif

