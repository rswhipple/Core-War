#ifndef _CORE_H_
#define _CORE_H_
#include "op.h"

// function prototypes
core_t *init_core(champion_t *head, flag_t *flags);
void calc_cursor_indices(core_t **core, champion_t *head);
int load_champions(core_t *core);

#endif
