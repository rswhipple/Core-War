 #include "../include/op.h"
#include "../include/memory.h"


// free everything
void cleanup(champion_t *head, core_t *core) {
    free_champions(head);
    free(core);
}

// free champions
void free_champions(champion_t *head) {
    champion_t *curr = head;
    champion_t *next = head->next; 
    while (curr) {
        free(curr->champ_header);
        free(curr);
        curr = next;
        if (next) {
            next = next->next;
        }
    }
}

inst_t init_inst(void) {
    inst_t holder = {
        .opcode = 0,
        .param_desc = 0,
        .value_1 = 0,
        .value_2 = 0,
        .value_3 = 0,
    };

    return holder;
}

inst_array_t *init_inst_array(int size) {
    inst_array_t *new = malloc(sizeof(inst_array_t));
    new->array = malloc(sizeof(inst_t*) * size);
    new->size = size;

    for (int i = 0; i < size; i++) new->array[i] = NULL;

    return new;
}

void free_inst_array(inst_array_t *inst) {
    for (int i = 0; i < inst->size; i++) free(inst->array[i]);
    free(inst);
}