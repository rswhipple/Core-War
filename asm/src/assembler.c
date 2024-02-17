#include "../include/asm.h"

// convert instruction to machine code
int write_header(FILE *cor, t_header *header) 
{
    // Header
    size_t bytes_written = fwrite(header, sizeof(t_header), 1, cor);

    // ERROR + EXIT
    if (bytes_written != 2192) {  // TODO double check size
        return EXIT_FAILURE;
    }

    free(header);

    return EXIT_SUCCESS;
}

int write_instructions(FILE *cor, t_array *instructions) 
{
    int i = 0;
    while (i < instructions->size) {
        int len = my_strlen(instructions->array[i]);
        size_t bytes_written = fwrite(instructions->array[i], len, 1, cor);

        // ERROR + EXIT
        if (bytes_written != len) {  // TODO double check size
            return EXIT_FAILURE;
        }
        free(instructions->array[i]);
        i++;
    }

    free(instructions);

    return EXIT_SUCCESS;
}
