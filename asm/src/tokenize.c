#include "../include/tokenize.h"
#include "../include/helper.h"
#include "../include/memory.h"


t_array* tokenizer(char* param_1, char* param_2)
{
    if (strlen(param_1) <= 0) {
        return 0;
    }

    int size = number_of_toks(param_1, param_2);
    t_array *tokens = init_t_array(size);
    parse_toks(param_1, param_2, &tokens);
    
    return tokens; 
}


int number_of_toks(char* string, char* separator) 
{
    int i = 0; int j = 0;
    int len_str = strlen(string);
    int len_chars = strlen(separator);
    int count = 1;

    while (i < len_str) {
        while (j < len_chars) {
            if (string[i] == separator[j]) {
                count++;
            }
            j++;
        }
        i++;
        j = 0;
    }

    return count;
}

void parse_toks(char* param_1, char* param_2, t_array **tokens) 
{
    int i = 0;
    int len = strlen(param_1);
    char buffer[100];
    int string_index = 0;
    
    while (i < len) {
        while (i < len) {
            if (my_strchr(param_2, param_1[i]) == NULL) {
                break;
            }
            i++;
        }

        int j = 0;

        while (i < len) {
            if (my_strchr(param_2, param_1[i]) != NULL) {
                break;
            }
            buffer[j] = param_1[i];
            i++;
            j++;
        }

        if (j > 0) {
            buffer[j] = '\0';
            (*tokens)->array[string_index] = malloc(sizeof(char) * (strlen(buffer) + 1));
            my_strcpy((*tokens)->array[string_index], buffer);
            string_index++;
        }

    }
}

