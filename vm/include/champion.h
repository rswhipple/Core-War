#ifndef _CHAMPION_H_
#define _CHAMPION_H_
#include "op.h"
#include "vm_parse.h"

// function prototypes
champion_t *create_champ(flag_t *flags, char *filename);
champion_t *init_champion(flag_t *flags);                    
cursor_t *init_cursor(flag_t *flags);
int read_file(champion_t **champ, int fd);  // parses .cor file into champion

#endif