#include "../include/op_helper.h"


void update_cursor(core_t *core, cursor_t *cursor, int i) {
	cursor->current_inst += 1;
	if (cursor->current_inst == cursor->num_inst) {
		cursor->ac = cursor->index_start;
		cursor->current_inst = 1;
	} else {
		cursor->ac += i;
	}
}

void update_cycles(core_t **core) {
	(*core)->cycle_count += 1;
	(*core)->total_cycles += 1;
	if ((*core)->cycle_count == (*core)->cycle_to_die) {
		(*core)->cycle_count = 0;
		(*core)->live_count += 1;
		if ((*core)->live_count == (*core)->nbr_live) {
			(*core)->live_count = 0;
		}
		is_alive(*core);
		print_stats(*core);
	}
}


// update the champion's carry flag if the previous operation returns 0
void update_carry(cursor_t *cursor, int dest_reg) {
  if (cursor->reg[dest_reg] == 0) {
    cursor->carry = 1;
  }
}

int get_reg(core_t *core, cursor_t *cursor, int i) {
	return (int)core->memory[cursor->ac + i];
}


int get_dir(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;

	result = (MASK_FF(core->memory[MOD(cursor->ac + i)]) << 24) |
				(MASK_FF(core->memory[MOD(cursor->ac + i + 1)]) << 16) |
				(MASK_FF(core->memory[MOD(cursor->ac + i + 2)]) << 8) |
				MASK_FF(core->memory[MOD(cursor->ac + i + 3)]);

	return (int)result;
}

int get_label(core_t *core, cursor_t *cursor, int i)
{
	unsigned int result;

	result = (0x00 << 24) |
            	(MASK_FF(core->memory[MOD(cursor->ac + i + 1)]) << 16) |
                (MASK_FF(core->memory[MOD(cursor->ac + i + 2)]) << 8) |
                MASK_FF(core->memory[MOD(cursor->ac + i + 3)]);

	return (int)result;
}

int	get_ind(core_t *core, cursor_t *cursor, int i)
{
	unsigned short result;

	i += cursor->ac;
	result = ((MASK_FF(core->memory[MOD(i)]) << 8) | MASK_FF(core->memory[MOD(i + 1)]));

	return (int)result;
}

void is_alive(core_t *core) {}

void print_stats(core_t *core) {}

void add_cycle(cursor_t *cursor) {}