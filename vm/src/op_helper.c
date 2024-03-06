#include "../include/op_helper.h"


void update_cursor(core_t *core, cursor_t *cursor, int i) {
    
}


void update_cycles(core_t *core, cursor_t *cursor) {

}


// update the champion's carry flag if the previous operation returns 0
void update_carry(cursor_t *cursor, int dest_reg) {
  if (cursor->reg[dest_reg] == 0) {
    cursor->carry = 1;
  }
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