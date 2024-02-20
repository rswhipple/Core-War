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

#define COMMENT_CHAR '#'
#define LABEL_CHAR ':'
#define DIRECT_CHAR '%'
#define SEPARATOR_CHAR ','
#define SEPARATOR_SET ", \t"

#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

/* size (in bytes) */
#define IND_SIZE 2
#define DIR_SIZE 4

#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"

// define commands
#define live 0x01
#define ld 0x02
#define st 0x03 
#define add 0x04
#define sub 0x05
#define and 0x06
#define or 0x07
#define xor 0x08
#define zjmp 0x09
#define ldi 0x0a
#define sti 0x0b
#define fork 0x0c
#define lld 0x0d
#define lldi 0x0e
#define lfork 0x0f
#define aff 0x10

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

typedef struct s_arg {
    int type;
    char *arg;
} t_arg;

typedef struct s_arg_node {
    int count;
    int num_bytes;
    char *label;
    char *command;
    t_arg **array;
    struct s_arg_node *next;
} t_node;

// function prototypes
int write_header(FILE *cor, t_header *header);
int write_inst(FILE *cor, t_node *head);
void write_int_big_end(FILE *cor, int num);
void print_usage();

#endif