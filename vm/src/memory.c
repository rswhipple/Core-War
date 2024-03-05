 #include "../include/op.h"
#include "../include/memory.h"


// free everything
void cleanup(core_t *core) {
    free_champions(core->champions);
    free(core);
}

// free champions
void free_champions(champion_t *head) {
    champion_t *curr = head;
    champion_t *next = head->next; 
    while (curr) {
        free(curr->cursor);
        free(curr->name);
        free(curr->comment);
        free(curr);
        curr = next;
        if (next) {
            next = next->next;
        }
    }
}


char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}

char *init_and_strncpy(char *src) {
    int len = my_strlen(src);
    char *str = init_str(len);
    my_strcpy(str, src);

    return str;
}


// inst_t *init_inst(void) {
//     inst_t *new = malloc(sizeof(inst_t));
//     new->opcode = 0;
//     new->param_desc = 0;
//     new->value_1 = 0;
//     new->value_2 = 0;
//     new->value_3 = 0;

//     return new;
// }

// inst_t **init_inst_array(int size) {
//     inst_t **new = malloc(sizeof(inst_t*) * size);

//     for (int i = 0; i < size; i++) new[i] = init_inst();

//     return new;
// }

// void free_inst_array(inst_t **inst, int size) {
//     for (int i = 0; i < size; i++) free(inst[i]);
//     free(inst);
// }