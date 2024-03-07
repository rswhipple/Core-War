#ifndef _VM_PARSE_H_
#define _VM_PARSE_H_
#include "op.h"

// function prototypes
champion_t *parse_args(int argc, char **argv, flag_t **flags);
flag_t *init_flag();
void print_usage();

#endif