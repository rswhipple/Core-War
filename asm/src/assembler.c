#include "../include/helper.h"
#include "../include/memory.h"
#include "../include/tokenize.h"

// write binary into file
int write_header(FILE *cor, t_header *header) 
{
    // Header
    write_int_big_end(cor, header->magic);
    size_t result = fwrite(header->prog_name, sizeof(header->prog_name), 1, cor);
    if (result != 1) return EXIT_FAILURE; 
    write_int_big_end(cor, header->prog_size);
    result = fwrite(header->comment, sizeof(header->comment), 1, cor);
    if (result != 1) return EXIT_FAILURE; 

    return EXIT_SUCCESS;
}


int write_inst(FILE *cor, t_node *inst) 
{
    size_t result;
    t_node *tmp = inst;
    t_node *next = NULL;
    u_int8_t byte_1 = 0;

    while (tmp) {
        next = tmp->next;   // save link to next node

        if ((byte_1 = get_command(cor, tmp->command)) <= 0) return EXIT_FAILURE;
        fwrite(&byte_1, sizeof(byte_1), 1, cor);
        printf("command = %i\n", byte_1);

        u_int8_t *bytes = get_values(tmp);
        if (!bytes) return EXIT_FAILURE;
        
        int i = 0;
        while (i < tmp->num_bytes - 2) {
            fwrite(&bytes[i], sizeof(bytes[i]), 1, cor);
            i++;
        }
        tmp = next;
    }

    return EXIT_SUCCESS;
}

void write_int_big_end(FILE *cor, int num) {
    u_int8_t bytes[4];
    bytes[0] = (num >> 24) & 0xFF;
    bytes[1] = (num >> 16) & 0xFF;
    bytes[2] = (num >> 8) & 0xFF;
    bytes[3] = num & 0xFF;

    fwrite(bytes, sizeof(bytes), 1, cor);
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

u_int8_t *get_values(t_node *inst) {
    int tmp_counter = 1;
    u_int8_t *array = init_int(14);
    int i = 0;

    while (i < 4) {
        while (i < inst->count) {
            array[0] <<= 2; // shifting to make room for next 2 bits
            array[0] |= inst->array[i]->type & 0x03;
            if (inst->array[i]->type == 1) {
                array[tmp_counter] = my_atoi(inst->array[i]->arg);  // set byte array[tmp_counter]
                tmp_counter++;  // increment tmp_counter by 1
            }
            if (inst->array[i]->type == 2) {
                u_int32_t num = my_atoi(inst->array[i]->arg);

                // handle direct labels
                if (inst->array[i]->arg[0] == ':') num = 0;
                printf("direct num = %i\n", num);

                array[tmp_counter] = num & 0xFF; 
                array[tmp_counter + 1] = (num >> 8) & 0xFF;
                array[tmp_counter + 2] = (num >> 16) & 0xFF;
                array[tmp_counter + 3] = (num >> 24) & 0xFF;
                tmp_counter += 4;   // increment tmp_counter by 4
            }
            if (inst->array[i]->type == 3) {
                u_int16_t num = my_atoi(inst->array[i]->arg);
                printf("indirect num = %i\n", num);
                array[tmp_counter] = num & 0xFF; 
                array[tmp_counter + 1] = (num >> 8) & 0xFF;
                tmp_counter += 2;   // increment tmp_counter by 2
            }
            i++;
        }
        array[0] <<= 2;
        i++;
    }
    if (tmp_counter != inst->num_bytes - 1) {
        printf("tmp_counter = %i\n", tmp_counter);
        my_puterror("Parsing Error: in get_values(), fewer bytes than expected\n");
        return NULL;
    }

    return array;
}

