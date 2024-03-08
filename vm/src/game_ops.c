#include "../include/game_ops.h"


void update_cursor(core_t *core, cursor_t *cursor, int i) {
	cursor->current_inst += 1;
	if (cursor->current_inst == cursor->num_inst) {
		cursor->ac = cursor->index_start;
		cursor->current_inst = 1;
	} else {
		cursor->ac += i;
	}
}

int update_cycles(core_t **core) {
	(*core)->cycle_count += 1;
	(*core)->total_cycles += 1;
	if ((*core)->cycle_count == (*core)->cycle_to_die) {
		(*core)->cycle_count = 0;
		(*core)->live_count += 1;
		if ((*core)->live_count == (*core)->nbr_live) {
			(*core)->live_count = 0;
			(*core)->cycle_to_die -= (*core)->cycle_delta;
		}
		if ((*core)->total_cycles == (*core)->dump) {
			game_over(*core, true);
			return 1;
		}
		if (is_alive(*core)) {
			print_stats(*core);
			game_over(*core, false);
			return 1;
		}
	}
	print_stats(*core);
	return 0;
}

void update_carry(cursor_t *cursor, int dest_reg) {
  if (cursor->reg[dest_reg] == 0) {
    cursor->carry = 1;
  }
}

int get_reg(core_t *core, cursor_t *cursor, int i) {
	int r = (int)core->memory[cursor->ac + i];

	if (r < 0 | r > 16) r = -1;
	return r;
}

int get_dir(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;
	u_int8_t byte;
	byte = (MASK_FF(core->memory[(cursor->ac + i)]) << 24);

	if (byte == 0xFF) return get_label(core, cursor, i);

	result = (MASK_FF(core->memory[(cursor->ac + i)]) << 24) |
				(MASK_FF(core->memory[(cursor->ac + i + 1)]) << 16) |
				(MASK_FF(core->memory[(cursor->ac + i + 2)]) << 8) |
				(MASK_FF(core->memory[(cursor->ac + i + 3)]));

	return (int)result;
}

int get_label(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;

	result = (0x00 << 24) |
            	(MASK_FF(core->memory[(cursor->ac + i + 1)]) << 16) |
                (MASK_FF(core->memory[(cursor->ac + i + 2)]) << 8) |
                (MASK_FF(core->memory[(cursor->ac + i + 3)]));
	return (int)result;
}

int	get_ind(core_t *core, cursor_t *cursor, int i)
{
	unsigned short result;

	i += cursor->ac;
	result = ((MASK_FF(core->memory[(i)]) << 8) | MASK_FF(core->memory[(i + 1)]));

	return (int)result;
}

void add_cycle(int opcode, cursor_t *cursor) {
	cursor->cycle += 1;
	switch (opcode) {
		case 1:
			cursor->running = 9;
			break;
		case 2:
			cursor->running = 4;
			break;
		case 3:
			cursor->running = 4;
			break;
		case 4:
			cursor->running = 9;
			break;
		case 5:
			cursor->running = 9;
			break;
		case 6:
			cursor->running = 5;
			break;
		case 7:
			cursor->running = 5;
			break;
		case 8:
			cursor->running = 5;
			break;
		case 9:
			cursor->running = 19;
			break;
		case 10:
			cursor->running = 24;
			break;
		case 11:
			cursor->running = 24;
			break;
		case 12:
			cursor->running = 799;
			break;
		case 13:
			cursor->running = 9;
			break;
		case 14:
			cursor->running = 49;
			break;
		case 15:
			cursor->running = 999;
			break;
		case 16:
			cursor->running = 1;
			break;
		default:
			break;
	}
}

void add_run_cycle(cursor_t *cursor) {
	cursor->cycle += 1;
	cursor->running -= 1;
}

void print_stats(core_t *core) {}

int is_alive(core_t *core) {
	champion_t *tmp = core->champions;
	int nbr_living = 0;
	while (tmp) {
		if (tmp->cursor->live) nbr_living++;
		else {
			tmp->cursor->dead = true;
			announce_death(tmp);
		}
		tmp = tmp->next;
	}

	if (nbr_living <= 1) return 1;

	return 0;
}

void announce_death(champion_t *champion) {
	champion->time_of_death = champion->cursor->cycle;
	printf("A champion has fallen, %s, id #%i is pronounced dead at its %i cycle.\n", 
					champion->name, champion->id, champion->time_of_death);
}

void game_over(core_t *core, bool dump_flag) {
	champion_t *winner = NULL;
	champion_t *tmp = core->champions;

	if (dump_flag) {
		printf("--------------------------------------------\n");
    	printf("\n\tMighty competitors live on!\n\n\n");
    	printf("\nThe war is a draw\n\n\n");
		while (tmp) {
			if (tmp->cursor->live) print_draw(tmp);
			tmp = tmp->next;
		}
		printf("--------------------------------------------\n\n");
    	printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
	} else {
		while (tmp) {
			if (tmp->cursor->live) winner = tmp;
			tmp = tmp->next;
		}
	}

	if (!winner) calc_tie(core);
	else print_winner(winner);

}

void calc_tie(core_t *core) {
	printf("--------------------------------------------\n");
    printf("\n\tThe war is over and all champions are dead\n\n\n");
    printf("\nThe last men standing were ...\n\n\n");
	champion_t *last_man_standing = core->champions;
	while (last_man_standing) {
		if (!last_man_standing->time_of_death) print_tie(last_man_standing);
		last_man_standing = last_man_standing->next;
	}
	printf("--------------------------------------------\n\n");
    printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
}

void print_winner(champion_t *champion) {
    printf("--------------------------------------------\n");
    printf("\n\tA winner has been declared\n\n\n");
    printf("\nThe winner of the war over the cores is...\n\n\n");
    printf("\n\t%s\n\n", champion->name);
    printf("--------------------------------------------\n\n");
    printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
}

void print_tie(champion_t *champion) {
    printf("\n\t%s\n\n", champion->name);
}

void print_draw(champion_t *champion) {
    printf("\n\t%s lives to fight another day.\n\n", champion->name);
}