#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"
#include "vm_parse.h"

#define BUF_SIZE 512

// function prototypes
champion_t *init_champion(flag_t *flags);                       // initializes an empty champion
champion_t *create_champion(flag_t *flags, char *filename);     // calls init_champion and read_file
int read_file(champion_t **champ, int fd);                      // parses .cor file into champion
int convert_to_inst(u_int8_t *buf, size_t prog_size);
void print_header(header_t *header);                            // tests whether header content was parsed correctly
void print_inst_buf(header_t *header, u_int8_t *buf, size_t size);
void free_champion(champion_t *champ);                          // frees champion
void print_champions(champion_t *head);                         // print champion contents
#endif