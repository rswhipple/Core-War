#include "../include/helper.h"
#include "../include/memory.h"
#include "../include/tokenize.h"

// write binary into file
int write_header(FILE *cor, t_header *header) 
{
    // Header
    write_int_big_end(cor, header->magic);
    size_t bytes_written = fwrite(header->prog_name, sizeof(header->prog_name), 1, cor);
    if (bytes_written != 1) return EXIT_FAILURE; 
    write_int_big_end(cor, header->prog_size);
    bytes_written = fwrite(header->comment, sizeof(header->comment), 1, cor);
    if (bytes_written != 1) return EXIT_FAILURE; 

    return EXIT_SUCCESS;
}


int write_inst(FILE *cor, t_node *inst) 
{
    // int i = 0;
    // while (i < inst->size) {
    //     int len = my_strlen(inst->array[i]);
    //     size_t bytes_written = fwrite(inst->array[i], len, 1, cor);
    //     if (bytes_written != 1) return EXIT_FAILURE;
    //     free(inst->array[i]);
    //     i++;
    // }

    // free(inst);

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


