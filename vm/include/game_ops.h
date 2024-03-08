#ifndef OP_HELPER_H
#define OP_HELPER_H
#include "op.h"

// function prototypes
void update_cursor(core_t *core, cursor_t *cursor, int i);
int update_cycles(core_t **core);
void update_carry(cursor_t *cursor, int dest_reg);
int get_reg(core_t *core, cursor_t *cursor, int i);
int get_dir(core_t *core, cursor_t *cursor, int i);
int get_label(core_t *core, cursor_t *cursor, int i);
int	get_ind(core_t *core, cursor_t *cursor, int i);
void add_cycle(int opcode, cursor_t *cursor);
int is_alive(core_t *core);
void game_over(core_t *core);
void calc_tie(core_t *core);
void print_stats(core_t *core);
void print_winner(champion_t *core);
void print_tie(champion_t *core);

#endif