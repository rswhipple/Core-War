#include "op.h"
#include "memory.h"

// free champion and core
void cleanup(champion_t *head, core_t *core) {
  free_champions(head);
  free(core);
}

// free champions
void free_champions(champion_t *head) {
  champion_t *curr = head;
  champion_t *next = curr;
  while (curr) {
    curr = curr->next;
    free(next->champ_header);
    free(next);
    next = curr;
  }
}

