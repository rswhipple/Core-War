#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"

// function prototypes
champion_t *init_champion(void);
int read_champion(champion_t *champ, char *filename);         // reads champion from file
header_t *get_header(char *filename, int fd);                  // returns header of champion
op_t *get_instructions(char *filename, int fd);         // returns array of instructions
void free_champion(champion_t *champ);
void load_champion(champion_t *champ, char *filename);

#endif