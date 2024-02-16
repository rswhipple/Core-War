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
int write_header(int fd, t_header* header);
t_header *init_header(void);

#endif