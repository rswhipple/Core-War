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
        uint32_t little_end_hex = 0;
        uint32_t little_end_hex_32 = 0;

        u_int8_t *bytes = get_values(tmp);
        if (!bytes) return EXIT_FAILURE;

        if ((byte_1 = get_command(cor, tmp->command)) <= 0) return EXIT_FAILURE;
        
        if (tmp->num_bytes <= 4) {
            little_end_hex = byte_1 | (bytes[0] << 8) | (bytes[1] << 16) | (bytes[2] << 24);
        } else {
            little_end_hex = byte_1 | (bytes[0] << 8) | (bytes[1] << 16) | (bytes[2] << 24) |
                        (bytes[3] << 32) | (bytes[4] << 40) | (bytes[5] << 48) | (bytes[6] << 56);
        } 
        fwrite(little_end_hex, sizeof(little_end_hex), 1, cor);

        if (tmp->num_bytes > 8) {
            little_end_hex_32 = bytes[7] | (bytes[8] << 8) | (bytes[9] << 16) | (bytes[10] << 24);
            fwrite(little_end_hex_32, sizeof(little_end_hex_32), 1, cor);
        }
        if (tmp->num_bytes > 12) {
            int i = 11;
            while (i < tmp->num_bytes - 2) {
                fwrite(bytes[i], sizeof(bytes[i]), 1, cor);
                i++;
            }
        }

        printf("tmp->command = %s\n", tmp->command);    // TESTING
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
    u_int8_t *array = init_int(inst->num_bytes - 1);
    int i = 0;

    while (i < 4) {
        while (i < inst->count) {
            array[0] <<= 2; // shifting to make room for next 2 bits
            array[0] |= inst->array[i]->type & 0x03;
            if (inst->array[i]->type == 1) {
                // set byte array[tmp_counter]
                // increment tmp_counter by 1
            }
            if (inst->array[i]->type == 2) {
                // set byte array[tmp_counter]
                // increment tmp_counter by 4
            }
            if (inst->array[i]->type == 3) {
                // set byte array[tmp_counter]
                // increment tmp_counter by 2
            }
            i++;
        }
        array[0] <<= 2;
        i++;
    }
    if (tmp_counter != inst->num_bytes - 1) {
        my_puterror("Parsing Error: in get_values(), fewer bytes than expected\n");
        return NULL;
    }

    return array;
}

