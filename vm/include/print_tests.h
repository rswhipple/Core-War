#ifndef _PRINT_TESTS_H_
#define _PRINT_TESTS_H_
#include "op.h"

// function prototypes
void print_header(header_t *header);
void print_inst_buf(header_t *header, char *buf, size_t size);
void print_champions(champion_t *head);
#endif