#include "../include/asm.h"

// initialize header
t_header *init_header(void) {
    t_header *header = malloc(sizeof(t_header));
    header->magic = COREWAR_EXEC_MAGIC;
    memset(header->prog_name, 0, PROG_NAME_LENGTH); // TODO change to my_memset
    memset(header->comment, 0, COMMENT_LENGTH);     // TODO change to my_memset
    return header;
}

// convert instruction to machine code
int write_header(int fd, t_header* header) 
{
    // Header
    ssize_t bytes_written = write(fd, header, sizeof(t_header));

    // ERROR + EXIT
    if (bytes_written != 500) {  // TODO figure out size
        return EXIT_FAILURE;
    }
    free(header);

    return EXIT_SUCCESS;
}
