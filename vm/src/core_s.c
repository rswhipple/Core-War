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
    core->cursors = head->cursor;
    core->total_champs = flags->num_champions;
    core->live_champs = flags->num_champions;
    core->cycle_to_die = CYCLE_TO_DIE;
    core->cycle_delta = CYCLE_DELTA;
    core->nbr_live = NBR_LIVE;
    core->dump = flags->dump;
    core->cycle = 0;
    core->counter = 0;

    calc_cursor_indices(&core, head);
    print_champions(core->champions);      // TESTING
    load_champions(core);

    free(flags);    // free flag_t

    return core;
}

void calc_cursor_indices(core_t **core, champion_t *head) {
    int offset = MEM_SIZE / (*core)->total_champs;

    champion_t *tmp = head;
    int i = 1;
    while (tmp) {
        tmp->cursor->index_start = offset * (i - 1);
        tmp->cursor->ac = tmp->cursor->index_start;
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

int load_champions(core_t *core) {
    champion_t *tmp_champ = core->champions;
    cursor_t *tmp = core->cursors;
    int i;
    int index;

    while (tmp_champ) {
        i = 0;
        index = tmp->index_start;

        printf("/////////////////// loading champ %s, id #%i into memory ///////////////////////\n", tmp_champ->name, tmp_champ->id);
        while (i < tmp_champ->string_len) {
            core->memory[index] = tmp_champ->string[i];
            printf("core->memory[%i]= %02hhx\n", index, core->memory[index]);
            index++; 
            i++;
        }

        tmp = tmp->next;
        tmp_champ = tmp_champ->next;
    }

    return EXIT_SUCCESS;
}

