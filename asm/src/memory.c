#include "../include/memory.h"
#include "../include/helper.h"

// initialize header struct
t_header *init_header(void) {
    t_header *header = malloc(sizeof(t_header));
    header->magic = 15369203;
    my_memset(header->prog_name, 0, PROG_NAME_LENGTH + 2); 
    header->prog_size = 0;
    my_memset(header->comment, 0, COMMENT_LENGTH + 2);     
    return header;
}

// initialize string array struct
t_array *init_t_array(int size) {
    t_array *new = malloc(sizeof(t_array));
    new->array = malloc(sizeof(char*) * size);
    new->size = 0;

    for (int i = 0; i < size; i++) { new->array[i] = NULL; }

    return new;
}

char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}
