#include "../include/game_ops.h"
#include "../include/print_tests.h"



void update_cursor(core_t *core, cursor_t **cursor, int i) {
	// cursor->current_inst += 1;
	printf("\nProgram #%i\nThe current ac is %i, inst is %i, total inst(s) in program = %i\n", 
			(*cursor)->parent->id, (*cursor)->ac, (*cursor)->current_inst, (*cursor)->num_inst);
	if ((*cursor)->current_inst >= (*cursor)->num_inst) {
		(*cursor)->ac = (*cursor)->index_start;
		(*cursor)->current_inst = 0;
	} else {
		(*cursor)->ac += i;
	}
	(*cursor)->ac = MOD((*cursor)->ac);
	print_cursor(*cursor);
}

int update_cycles(core_t **core) {
	(*core)->cycle_count += 1;
	(*core)->total_cycles += 1;
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Number of cycles left in this cycle_to_die %i\n", (*core)->cycle_to_die - (*core)->cycle_count);
	printf("Lives until cycle_delta %i\n\n", (*core)->nbr_live - (*core)->live_count);
	if ((*core)->cycle_count >= (*core)->cycle_to_die) {
		printf("The cycle_to_die is %i\n", (*core)->cycle_to_die);
		(*core)->cycle_count = 0;
		(*core)->live_count += 1;
		if ((*core)->live_count == (*core)->nbr_live) {
			(*core)->live_count = 0;
			(*core)->cycle_to_die -= (*core)->cycle_delta;
			printf("The cycle_to_die is now %i\n", (*core)->cycle_to_die);
			printf("Total number of cycles = %i\n", (*core)->total_cycles);
		}
		if ((*core)->total_cycles >= (*core)->dump) {
			game_over(*core, true);
			return 1;
		} else if (is_alive(*core)) {
			game_over(*core, false);
			return 1;
		}
		champion_t *tmp = (*core)->champions;
		while (tmp) {
			tmp->cursor->live = false;
			tmp = tmp->next;
		}
	}
	return 0;
}

void update_carry(cursor_t *cursor, int dest_reg) {
  if (cursor->reg[dest_reg] == 0) {
    cursor->carry = 1;
	printf("Updating carry of %s, #%i to 1.\n", cursor->parent->name, cursor->parent->id);
  } else {
	cursor->carry = 0;
  }
}


int get_reg(core_t *core, cursor_t *cursor, int i) {
	int byte = (int)core->memory[cursor->ac + i];

	if (byte < 0 | byte > 16) byte = -1;
	return byte;
}

int get_reg_value(core_t *core, cursor_t *cursor, int i) {
	int r = (int)core->memory[cursor->ac + i];
	if (r < 0 | r > 16) return 0;

	int reg_value = cursor->reg[r];

	return reg_value;
}


int get_bytes(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;

	result = (MASK_FF(core->memory[(cursor->ac + i)]) << 24) |
				(MASK_FF(core->memory[(cursor->ac + i + 1)]) << 16) |
				(MASK_FF(core->memory[(cursor->ac + i + 2)]) << 8) |
				(MASK_FF(core->memory[(cursor->ac + i + 3)]));

	return (int)result;
}

int get_dir(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;
	u_int8_t byte;
	byte = (MASK_FF(core->memory[(cursor->ac + i)]));

	if (byte == 0xFF) return get_label(core, cursor, i);

	result = (MASK_FF(core->memory[(cursor->ac + i)]) << 24) |
				(MASK_FF(core->memory[(cursor->ac + i + 1)]) << 16) |
				(MASK_FF(core->memory[(cursor->ac + i + 2)]) << 8) |
				(MASK_FF(core->memory[(cursor->ac + i + 3)]));

	return (int)result;
}

int get_label(core_t *core, cursor_t *cursor, int i)
{
	unsigned int offset;

	offset = (0x00 << 24) |
            	(MASK_FF(core->memory[(cursor->ac + i + 1)]) << 16) |
                (MASK_FF(core->memory[(cursor->ac + i + 2)]) << 8) |
                (MASK_FF(core->memory[(cursor->ac + i + 3)]));
	
	// finish label logic
	// printf("Label offset = %i\n", offset);
	unsigned int result = core->memory[MOD(cursor->ac + offset)];

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
		case 0:
			cursor->running = 9;
			printf("%s, #%i is running \"live\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 1:
			cursor->running = 4;
			printf("%s, #%i is running \"ld\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 2:
			cursor->running = 4;
			printf("%s, #%i is running \"st\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 3:
			cursor->running = 9;
			printf("%s, #%i is running \"add\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 4:
			cursor->running = 9;
			printf("%s, #%i is running \"sub\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 5:
			cursor->running = 5;
			printf("%s, #%i is running \"and\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 6:
			cursor->running = 5;
			printf("%s, #%i is running \"or\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 7:
			cursor->running = 5;
			printf("%s, #%i is running \"xor\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 8:
			cursor->running = 19;
			printf("%s, #%i is running \"zjmp\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 9:
			cursor->running = 24;
			printf("%s, #%i is running \"ldi\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 10:
			cursor->running = 24;
			printf("%s, #%i is running \"sti\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 11:
			cursor->running = 799;
			printf("%s, #%i is running \"fork\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 12:
			cursor->running = 9;
			printf("%s, #%i is running \"lld\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 13:
			cursor->running = 49;
			printf("%s, #%i is running \"lldi\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 14:
			cursor->running = 999;
			printf("%s, #%i is running \"lfork\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		case 15:
			cursor->running = 1;
			printf("%s, #%i is running \"aff\".\n", 
                cursor->parent->name, cursor->parent->id);
			break;
		default:
			break;
	}
	cursor->opcode = opcode;
}

void add_run_cycle(cursor_t *cursor) {
	printf("%s, #%i is running opcode %i, %i cycles left.\n", 
        cursor->parent->name, cursor->parent->id, cursor->opcode, cursor->running);
	cursor->cycle += 1;
	cursor->running -= 1;
}

void print_stats(core_t *core) {
	printf("At the end of battle:\n\n\ttotal cycles = %i\n\n", core->total_cycles);
	printf("\tcycle_to_die = %i\n\n", core->cycle_to_die);
}

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
		print_stats(core);
		while (tmp) {
			if (tmp->cursor->live) print_draw(tmp);
			tmp = tmp->next;
		}
		printf("--------------------------------------------\n\n");
    	printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
		return;
	} else {
		while (tmp) {
			if (tmp->cursor->live) winner = tmp;
			tmp = tmp->next;
		}
	}

	if (!winner) calc_tie(core);
	else print_winner(core, winner);

}

void calc_tie(core_t *core) {
	printf("--------------------------------------------\n");
    printf("\nThe war is over and all champions are dead\n\n\n");
	print_stats(core);
    printf("\nThe last men standing were ...\n\n\n");
	champion_t *last_man_standing = core->champions;
	// TODO fix logic
	while (last_man_standing) {
		if (last_man_standing->time_of_death) print_tie(last_man_standing);
		last_man_standing = last_man_standing->next;
	}
	printf("--------------------------------------------\n\n");
    printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
}

void print_winner(core_t *core, champion_t *champion) {
    printf("--------------------------------------------\n");
    printf("\n\tA winner has been declared\n\n\n");
    printf("\nThe winner of the war over the cores is...\n\n");
    printf("\n\t%s\n\n", champion->name);
	print_stats(core);
    printf("--------------------------------------------\n\n");
    printf("~~~###/// THE CORE WARS ARE OVER ///###~~~\n\n");
}

void print_tie(champion_t *champion) {
    printf("\n\t%s\n\n", champion->name);
}

void print_draw(champion_t *champion) {
    printf("\n%s #%i lives to fight another day.\n\n", champion->name, champion->id);
}