#ifndef HELPER_H
#define HELPER_H
#include "asm.h"

// function prototypes
int my_atoi(char *num);
int my_strlen(char* str);
char* my_strncpy(char* dst, char* src, int n);
char* my_strcpy(char* dst, char* src);
char* my_strcat(char *dst, char *src);
int my_strncmp(char* str_1, char* str_2, int index);
void my_putstr(char *str);

#endif