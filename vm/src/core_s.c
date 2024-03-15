#include "../include/op.h"
#include "../include/core.h"
#include "../include/memory.h"
#include "../include/print_tests.h"

// initialize core
core_t *init_core(champion_t *head, flag_t *flags) {
    core_t *core = malloc(sizeof(core_t));
    if (core == NULL) {
        return NULL;
    }
    memset(core->memory, 0, MEM_SIZE);
    core->champions = head;
    core->cursors = head->cursor;
    core->total_champs = flags->num_champions;
    core->cycle_to_die = 1000; //CYCLE_TO_DIE;
    core->cycle_delta = CYCLE_DELTA;
    core->nbr_live = NBR_LIVE;
    core->dump = flags->dump;
    if (core->dump == 0) core->dump = NBR_DUMP;

    core->cycle_count = 0;
    core->live_count = 0;
    core->total_cycles = 0;

    calc_cursor_indices(&core, core->champions);
    load_champions(core);

    free(flags);

    return core;
}

void calc_cursor_indices(core_t **core, champion_t *head) {
    int offset = MEM_SIZE / (*core)->total_champs;
    // TODO add -a flag handler

    champion_t *tmp = head;
    int i = 1;
    while (tmp) {
        tmp->cursor->index_start = offset * (i - 1);
        tmp->cursor->ac += tmp->cursor->index_start;
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

        printf("//// loading champ %s, id #%i into memory ////\n\n", tmp_champ->name, tmp_champ->id);
        while (i < tmp_champ->string_len) {
            core->memory[index] = tmp_champ->string[i];
            index++; 
            i++;
        }

        printf("tmp->num_inst = %i\n", tmp->num_inst);
        printf("tmp->str_len = %i\n\n", tmp_champ->string_len);
        printf("tmp->index_start = %i\n\n", tmp->index_start);

        tmp = tmp->next;
        tmp_champ = tmp_champ->next;
    }

    return EXIT_SUCCESS;
}

