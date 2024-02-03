#ifndef _VM_PARSE_H_
#define _VM_PARSE_H_
#include "op.h"

typedef struct flag_s {
    int num_champions;
    int dump;
    int id;
    int address;
} flag_t;

// function prototypes
int parse_args(int argc, char **argv);
flag_t init_flag();
void print_usage();

#endif