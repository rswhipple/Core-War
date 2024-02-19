#include "../include/asm.h"
#include "../include/helper.h"

// convert instruction to machine code
char *convert_inst(char *src) {
    return src;
}

// write binary into file
int write_header(FILE *cor, t_header *header) 
{
    // Header
    size_t bytes_written = fwrite(header, sizeof(t_header), 1, cor);

    // ERROR + EXIT
    if (bytes_written != 2192) return EXIT_FAILURE; // TODO double check size

    free(header);

    return EXIT_SUCCESS;
}

int write_inst(FILE *cor, t_array *inst) 
{
    int i = 0;
    while (i < inst->size) {
        int len = my_strlen(inst->array[i]);
        size_t bytes_written = fwrite(inst->array[i], len, 1, cor);

        // ERROR + EXIT
        if (bytes_written != len) {  // TODO double check size
            return EXIT_FAILURE;
        }
        free(inst->array[i]);
        i++;
    }

    free(inst);

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