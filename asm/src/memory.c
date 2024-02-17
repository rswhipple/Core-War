#include "../include/memory.h"

// initialize header struct
t_header *init_header(void) {
    t_header *header = malloc(sizeof(t_header));
    header->magic = COREWAR_EXEC_MAGIC;
    memset(header->prog_name, 0, PROG_NAME_LENGTH); // TODO change to my_memset
    memset(header->comment, 0, COMMENT_LENGTH);     // TODO change to my_memset
    return header;
}

// initialize string array struct
t_array *init_t_array(void) {
    t_array *new = malloc(sizeof(t_array));
    new->size = 0;
    new->array = NULL;

    return new;
}

char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}

// void free_t_array(t_array *arr);

// void free_header(t_header *header);