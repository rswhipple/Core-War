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

inst_t *init_inst(void) {
    inst_t *new = malloc(sizeof(inst_t));
    new->opcode = 0;
    new->param_desc = 0;
    new->value_1 = 0;
    new->value_2 = 0;
    new->value_3 = 0;

    return new;
}

inst_t **init_inst_array(int size) {
    inst_t **new = malloc(sizeof(inst_t*) * size);

    for (int i = 0; i < size; i++) new[i] = init_inst();

    return new;
}

void free_inst_array(inst_t **inst, int size) {
    for (int i = 0; i < size; i++) free(inst[i]);
    free(inst);
}