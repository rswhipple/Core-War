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

u_int8_t *init_int(int size) { 
    u_int8_t *array = malloc((size) * sizeof(u_int8_t));
    for (int i = 0; i < size; i++) array[i] = 0;

    return array;
}

t_node *init_node(int size) {
    t_node *new = malloc(sizeof(t_node));
    new->count = 0;
    new->num_bytes = 2;
    new->label = NULL;
    new->command = NULL;
    new->array = malloc(sizeof(t_arg *) * size);
    new->next = NULL;

    return new;
}

t_arg *init_arg(void) {
    t_arg *new = malloc(sizeof(t_arg));
    new->arg = NULL;
    new->type = 0;

    return new;
}

t_array *init_dict(void) {
    t_array *dict = malloc(sizeof(t_array));
    dict->size = 16;
    dict->array[16] = malloc(sizeof(char *));

    dict->array[0] = "live";
    dict->array[1] = "ld";
    dict->array[2] = "st";
    dict->array[3] = "add"; 
    dict->array[4] = "sub";  
    dict->array[5] = "and"; 
    dict->array[6] = "or"; 
    dict->array[7] = "xor"; 
    dict->array[8] = "zjmp"; 
    dict->array[9] = "ldi"; 
    dict->array[10] = "sti";
    dict->array[11] = "fork"; 
    dict->array[12] = "lld"; 
    dict->array[13] = "lldi"; 
    dict->array[14] = "lfork";
    dict->array[15] = "aff"; 

    return dict;
}

char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}

void free_dict(t_array *dict) {
    free(dict->array);
    free(dict);
}

void free_t_array(t_array *tokens) {
    int i = 0;
    while (i < tokens->size) {
        free(tokens->array[i]);
        i += 1;
    }
    free(tokens->array);
    free(tokens);
}

void free_nodes(t_node *head) {
    t_node *tmp = head;
    t_node *next;
    while (tmp) {
        next = tmp->next;
        free(tmp->label);
        free(tmp->command);

        int i = 0;
        while (i < tmp->count) {
            free_t_arg(tmp->array[i]);
            i += 1;
        }

        free(tmp->array);
        free(tmp);
        tmp = next;
    }
}

void free_t_arg(t_arg *arg) {
    free(arg->arg);
    free(arg);
}
