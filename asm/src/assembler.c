#include "../include/asm.h"

// convert instruction to machine code
int write_header(FILE *cor, t_header* header) 
{
    // Header
    size_t bytes_written = fwrite(&header, sizeof(t_header), 1, cor);

    // ERROR + EXIT
    if (bytes_written != 2192) {  // TODO double check size
        return EXIT_FAILURE;
    }

    free(header);

    return EXIT_SUCCESS;
}
