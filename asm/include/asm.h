#ifndef _ASM_H_
#define _ASM_H_
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define COREWAR_EXEC_MAGIC 0xea83f3
#define MAX_INSTRUCTIONS 40

// structs
typedef struct s_header {
  int magic;
  char prog_name[PROG_NAME_LENGTH + 1];
  int prog_size;
  char comment[COMMENT_LENGTH + 1];
} t_header;

typedef struct s_string_array {
    int size;
    char **array;
} t_array;

// function prototypes
char *convert_inst(char *src);
int write_header(FILE *cor, t_header *header);
int write_inst(FILE *cor, t_array *inst);
void write_int_big_end(FILE *cor, int num);

#endif