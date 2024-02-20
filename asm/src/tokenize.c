#include "../include/tokenize.h"
#include "../include/helper.h"


t_array* tokenizer(char* param_1, char* param_2)
{
    if (strlen(param_1) <= 0) {
        return 0;
    }

    t_array *output = malloc(sizeof(t_array));

    output->size = number_of_strings(param_1, param_2);
    output->array = array_substrings(param_1, param_2, output->size);
    
    return output; 
}


int number_of_strings(char* string, char* separator) 
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


char* my_strcpy(char* dst, char* src)
{
    int i;
    int len = strlen(src);

    for (i = 0; i < len; i++) {
        dst[i] = src[i]; 
    }

    return dst;
}

char** array_substrings(char* param_1, char* param_2, int count) 
{
    int i = 0;
    int len = strlen(param_1);
    char** strings = malloc(sizeof(char*) * count);
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
            strings[string_index] = malloc(sizeof(char) * (strlen(buffer) + 1));
            my_strcpy(strings[string_index], buffer);
            string_index++;
        }

    }
    
    return strings;
}

