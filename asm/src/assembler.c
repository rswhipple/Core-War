#include "../include/helper.h"
#include "../include/memory.h"
#include "../include/tokenize.h"

int write_header(FILE *cor, t_header *header) 
{
    size_t result = fwrite(header, sizeof(t_header), 1, cor);
    if (result != 1) return EXIT_FAILURE; 

    return EXIT_SUCCESS;
}


int write_inst(FILE *cor, t_node *head, t_prog_size *size) 
{
    size_t result;
    t_node *tmp = head;
    u_int8_t byte_1 = 0;

    while (tmp) {
        if ((byte_1 = get_command(cor, tmp->command)) <= 0) return EXIT_FAILURE;
        fwrite(&byte_1, sizeof(byte_1), 1, cor);
        size->curr_byte += 1;

        u_int8_t *curr_inst = get_values(head, tmp, size);
        if (!curr_inst) return EXIT_FAILURE;

        int i = 0;
        if (byte_1 == 0x01 || byte_1 == 0x09 || byte_1 == 0x0c || 
                    byte_1 == 0x0f || byte_1 == 0x10) {                  // check if command is type "special"
            i += 1;
            while (i < tmp->num_bytes) {
                fwrite(&curr_inst[i], sizeof(curr_inst[i]), 1, cor);
                i++;
            }
        } else {
            while (i < tmp->num_bytes - 1) {
                fwrite(&curr_inst[i], sizeof(curr_inst[i]), 1, cor);
                i++;
            }
        }
        
        tmp = tmp->next;
    }

    return EXIT_SUCCESS;
}


u_int8_t get_command(FILE *cor, char *command)
{
    command_map mappings[] = {
        { "live", live },
        { "ld", ld },
        { "st", st },
        { "add", add },
        { "sub", sub },
        { "and", and},
        { "or", or },
        { "xor", xor },
        { "zjmp", zjmp },
        { "ldi", ldi },
        { "sti", sti },
        { "fork", fork },
        { "lld", lld },
        { "lldi", lldi },
        { "lfork", lfork },
        { "aff", aff },
    };

    int num_mappings = 16;

    int i = 0;

    while (i < num_mappings) {
        if (my_strcmp(mappings[i].token, command) == 0) {
            return mappings[i].command;
        }
        i++;
    }

    return -1;
}

u_int8_t *get_values(t_node *head, t_node *inst, t_prog_size *size) {
    int tmp_counter = 1;
    u_int8_t *array = init_int(inst->num_bytes);
    int i = 0;

    while (i < 4) {
        while (i < inst->param_count) {
            array[0] <<= 2; // shifting to make room for next 2 bits
            array[0] |= inst->array[i]->type & 0x03;
            if (inst->array[i]->type == 1) {
                array[tmp_counter] = my_atoi(inst->array[i]->arg); 
                tmp_counter++;  // increment tmp_counter by 1
                size->curr_byte++;
            }
            if (inst->array[i]->type == 2) {
                u_int32_t num;

                // handle direct labels
                if (inst->array[i]->arg[0] == ':') {
                    char *label = inst->array[i]->arg + 1;
                    num = calculate_jump(head, inst, label, size);
                    array[tmp_counter] = 0xFF;
                } else {
                    num = my_atoi(inst->array[i]->arg);
                    array[tmp_counter] = (num >> 24) & 0xFF;
                }

                // Reverse the order of byte writing
                array[tmp_counter + 3] = num & 0xFF;
                array[tmp_counter + 2] = (num >> 8) & 0xFF;
                array[tmp_counter + 1] = (num >> 16) & 0xFF;
                tmp_counter += 4;   // increment tmp_counter by 4
                size->curr_byte += 4;
            }
            if (inst->array[i]->type == 3) {
                u_int16_t num = my_atoi(inst->array[i]->arg);
                array[tmp_counter + 1] = num & 0xFF; 
                array[tmp_counter] = (num >> 8) & 0xFF;
                tmp_counter += 2;   // increment tmp_counter by 2
                size->curr_byte += 2;
            }
            i++;
        }
        array[0] <<= 2;
        i++;
    }

    // TESTING print array
    // printf("--------------- Instruction #%i ---------------\n", inst->id);
    // // if (tmp_counter != inst->num_bytes - 1) {
    // //     printf("tmp_counter == %i, != %i\n", tmp_counter, inst->num_bytes - 1);
    // //     printf("Double check : in get_values(), fewer bytes than expected\n");
    // // }
    // i = 0;
    // while (i < tmp_counter) {
    //     printf("byte index %i in the instruction byte array = %02x\n", i, array[i]);
    //     i++;
    // }

    return array;
}

u_int32_t calculate_jump(t_node *head, t_node *inst, char *label, t_prog_size *size) {
    u_int32_t result = 0;
    t_node *tmp = head;

    while (tmp) {
        if (tmp->label && (my_strcmp(label, tmp->label)) == 0) {
            if (tmp->id - inst->id > 0) {
                result = tmp->offset - size->curr_byte + 1;
            } else {
                result = (u_int32_t)(MEM_SIZE - (size->curr_byte - tmp->offset) + 1);   // TODO double check +1 is correct
            }
            return result;
        }
        tmp = tmp->next;
    }

    return result;
}

void write_int_big_end(FILE *cor, int num) {
    u_int8_t bytes[4];
    bytes[0] = (num >> 24) & 0xFF;
    bytes[1] = (num >> 16) & 0xFF;
    bytes[2] = (num >> 8) & 0xFF;
    bytes[3] = num & 0xFF;

    fwrite(bytes, sizeof(bytes), 1, cor);
}
