#include "../include/memory.h"

t_array *init_t_array(void) {
    t_array *new = malloc(sizeof(t_array));
    new->size = 0;
    new->array = NULL;
}

char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}

void free_t_array(t_array *arr);