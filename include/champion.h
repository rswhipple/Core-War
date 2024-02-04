#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"
#include "vm_parse.h"

// function prototypes
champion_t *init_champion(flag_t *flags);                       // initializes an empty champion
champion_t *create_champion(flag_t *flags, char *filename);     // creates champion from file
int read_file(champion_t **champ, int fd);                      // parses champion file
void free_champion(champion_t *champ);                          // frees champion

#endif