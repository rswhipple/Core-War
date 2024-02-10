#include "../include/op.h"
#include "../include/core.h"
#include "../include/memory.h"

// initialize core
core_t *init_core(champion_t *head, flag_t *flags) {
    // initialize core
    core_t *core = malloc(sizeof(core_t));
    if (core == NULL) {
        return NULL;
    }
    memset(core->memory, 0, MEM_SIZE);  // initialize memory to 0
    core->champions = NULL;
    core->num_champions = flags->num_champions;
    core->cycle_to_die = CYCLE_TO_DIE;
    core->cycle_delta = CYCLE_DELTA;
    core->nbr_live = NBR_LIVE;
    core->dump = flags->dump;
    core->cycle = 0;

    core->load_champion = load_champion;

    free(flags);    // all information from flag_t has been recorded

    return core;
}

void load_champion(core_t *core, champion_t *champ) {

}
