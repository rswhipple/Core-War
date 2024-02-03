#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"

// function prototypes
champion_t *init_champion(flag_t *flags);                   // initializes an empty champion
int create_champion(flag_t *flags, char *filename);         // creates champion from file
header_t *get_header(int fd);                               // returns header of champion
op_t *get_instructions(champion_t *champ, int fd);             // returns array of instructions
void free_champion(champion_t *champ);                      // frees champion

#endif