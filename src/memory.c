 #include "../include/op.h"
#include "../include/memory.h"


// free everything
void cleanup(champion_t *head, code_t *core) {
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

