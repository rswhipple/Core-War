#include "../include/helper.h"
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

