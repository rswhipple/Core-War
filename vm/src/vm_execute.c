/*
    vm_execute needs to include

        1. a scheduler function (game_loop)

        2. print winner function
*/
#include "../include/op.h"

int game_loop(core_t *core) {
    bool no_winner;
    cursor_t *cursor;

    no_winner = true;
    cursor = core->cursors;
    while (no_winner) {
        if (cursor->flag) check_for_winner(core->champions, &no_winner);
        if (!cursor->dead) {
            execute_inst(core, cursor);
        }
        cursor = cursor->next;
    }

    print_winner(core);

    return EXIT_SUCCESS;
}

bool check_for_winner(champion_t *head, bool no_winner) {}
int execute_inst(core_t *core, cursor_t *cursor) {}
void print_winner(core_t *core) {}