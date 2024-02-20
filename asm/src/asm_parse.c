#include "../include/asm_parse.h"
#include "../include/helper.h"
#include "../include/memory.h"

int execute_asm(char *filename) {
    // init .cor file
    FILE *cor = create_cor_file(filename);

    // create header and instruction line storage
    t_header *header = init_header();
    t_node *inst_head = NULL;

    // open, read and transform .S file
    const char *read = "r";
    FILE *fp = fopen(filename, read);
    if (!fp) return EXIT_FAILURE;
    
    inst_head = read_file(fp, &header);
    fclose(fp);

    // write header
    if (write_header(cor, header)) return EXIT_FAILURE;
    free(header);

    // write instructions
    if (write_inst(cor, inst_head)) return EXIT_FAILURE;

    // cleanup
    free_nodes(inst_head);
    fclose(cor);

    return EXIT_SUCCESS;
}

t_node *read_file(FILE *fp, t_header **header) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    t_node *head = NULL;

    while ((nread = getline(&line, &len, fp)) != -1) {
        if (my_strncmp(line, NAME_CMD_STRING, 5) == 0) { 
            remove_line_title(header, line, 7);
        }
        else if (my_strncmp(line, COMMENT_CMD_STRING, 8) == 0) { 
            remove_line_title(header, line, 10);
        } 
        else if (nread == 1 || my_strncmp(line, "/n", 1) == 0) {
            continue;
        } else {
            if (!head) head = string_to_arg_array(line);
            else {
                t_node *tmp = head;
                while (tmp->next) tmp = tmp->next;
                tmp->next = string_to_arg_array(line);
            }
        }
    }
    
    return head;
}

FILE *create_cor_file(char *filename) {
    char *name = replace_ext(filename);
    const char *write = "wb";
    FILE *cor= fopen(name, write);
    return cor;
}

char *replace_ext(char *filename) {
    int len = my_strlen(filename);
    char *new_ext = "cor";
    char *new_filename = init_str(len + 2);
    my_strncpy(new_filename, filename, len);
    my_strcat(new_filename, new_ext);
    // my_putstr(new_filename);    // TESTING

    return new_filename;
}

void remove_line_title(t_header **header, char *line, int size) {
    my_strcpy((*header)->prog_name, line + size); 
    int copied_len = my_strlen((*header)->prog_name);
    (*header)->prog_name[copied_len - 2] = '\0';
    (*header)->prog_name[copied_len - 1] = '\0';
}


// convert instructions into tokens
t_node *string_to_node(char *src) {
    // create tokens from string
    t_array *tokens = tokenizer(src, SEPARATOR_SET);
    free(src);

    // init variables
    t_node *args = init_arg_array(4);
    int i = 0;
    
    // check for label
    int tok_len = my_strlen(tokens->array[0]);
    if (tokens->array[0][tok_len - 1] == LABEL_CHAR) {
        args->label = init_str(tok_len + 1);
        my_strcpy(args->label, tokens->array[0]);
        i++;
    }

    // find the command
    tok_len = my_strlen(tokens->array[i]);
    char *command = tokens->array[i];
    my_strcpy(args->label, tokens->array[i]);
    i++;

    // parse values into t_args
    while (i < tokens->size) {
        if (!tokens->array[i]) break;
        else if (tokens->array[i][0] == COMMENT_CHAR) continue;
        else if (tokens->array[i][0] == 'r') {
            token_to_arg(&args, tokens->array[i], 1);
            args->num_bytes++;
            args->count++;
        }
        else if (tokens->array[i][0] == DIRECT_CHAR) {
            token_to_arg(&args, tokens->array[i], 10);
            args->num_bytes += 4;
            args->count++;
        }
        else {
            token_to_arg(&args, tokens->array[i], 11);
            args->num_bytes += 2;
            args->count++;
        }
        i++;
    }
    
    // free token array
    free_t_array(tokens);

    return args;
}

void token_to_arg(t_node **args, char *tok, int type) 
{
    (*args)->array[(*args)->count] = init_arg();
    t_arg *tmp = (*args)->array[(*args)->count];
    tmp->arg = init_str(my_strlen(tok) + 1);
    my_strcpy(tmp->arg, tok);
    tmp->type = type;
}
