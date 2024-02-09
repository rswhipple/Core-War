#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"
#include "vm_parse.h"

// function prototypes
champion_t *init_champion(flag_t *flags);                       // initializes an empty champion
champion_t *create_champion(flag_t *flags, char *filename);     // calls init_champion and read_file
int read_file(champion_t **champ, int fd);                      // parses .cor file into champion
void free_champion(champion_t *champ);                          // frees champion
void print_champions(champion_t *head);                         // print champion contents
#endif