#include "../include/op.h"
#include "../include/core.h"
#include "../include/memory.h"
#include "../include/print_tests.h"

// initialize core
core_t *init_core(champion_t *head, flag_t *flags) {
    // initialize core
    core_t *core = malloc(sizeof(core_t));
    if (core == NULL) {
        return NULL;
    }
    memset(core->memory, 0, MEM_SIZE);
    core->champions = head;
    core->num_champions = flags->num_champions;
    core->cycle_to_die = CYCLE_TO_DIE;
    core->cycle_delta = CYCLE_DELTA;
    core->nbr_live = NBR_LIVE;
    core->dump = flags->dump;
    core->cycle = 0;

    load_champions(core, head);

    print_champions(head);


    // TODO figure out op_tab

    // TODO make champion_t list and cursor_t list circular

    free(flags);    // all information from flag_t has been recorded

    return core;
}

void load_champions(core_t *core, champion_t *head) {
    int offset = MEM_SIZE / core->num_champions;

    champion_t *tmp = head;
    int i = 1;
    while (tmp) {
        tmp->cursor->index_start = offset * (i - 1);
        if (tmp->next) {
            tmp->cursor->next = tmp->next->cursor;
        }
        else {
            tmp->cursor->next = head->cursor;
        }
        i++;
        tmp = tmp->next;
    }

}

