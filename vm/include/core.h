#include "op.h"
#include "vm_parse.h"

// function prototypes
core_t *init_core(champion_t *head, flag_t *flags);
void calc_cursor_indices(core_t **core, champion_t *head);
int load_champions(core_t *core);
