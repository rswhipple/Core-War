#include "../include/asm.h"

// convert instruction to machine code
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
