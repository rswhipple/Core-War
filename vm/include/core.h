#include "op.h"
#include "vm_parse.h"

// function prototypes
core_t *init_core(champion_t *head, flag_t *flags);
void load_champion(core_t *core, champion_t *champ);
void free_core(core_t *core);
