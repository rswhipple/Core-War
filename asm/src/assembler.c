#include "../include/helper.h"
#include "../include/memory.h"
#include "../include/tokenize.h"

// convert instruction to machine code
char *convert_inst(char *src) {
    // create tokens from string
    t_array *tokens = tokenizer(src, SEPARATOR_SET);
    free(src);

    // check if there is a label
    int i = 0;
    char *label = NULL;
    int first_tok_len = my_strlen(tokens->array[0]);
    if (tokens->array[0][first_tok_len - 1] == LABEL_CHAR) {
        label = tokens->array[0];           // TODO handle memory, this is being freed line 50
        i++;
    }

    // find the command
    char *command = tokens->array[i];       // TODO handle memory, this is being freed line 50
    i++;

    // parse tokens into t_arg_array struct
    int num_bytes = 2;
    t_arg_array *args = init_arg_array(4);

    while (i < tokens->size) {
        if (!tokens->array[i]) break;
        else if (tokens->array[i][0] == COMMENT_CHAR) continue;
        else if (tokens->array[i][0] == 'r') {
            token_to_arg(&args, tokens->array[i], 1);
            num_bytes++;
            args->count++;
        }
        else if (tokens->array[i][0] == DIRECT_CHAR) {
            token_to_arg(&args, tokens->array[i], 10);
            num_bytes += 4;
            args->count++;
        }
        else {
            token_to_arg(&args, tokens->array[i], 11);
            num_bytes += 2;
            args->count++;
        }
        i++;
    }
    
    // free token array
    free_t_array(tokens);

    // set the bytes
    u_int8_t bytes[num_bytes];

    return src;
}

// write binary into file
int write_header(FILE *cor, t_header *header) 
{
    // Header
    write_int_big_end(cor, header->magic);
    size_t bytes_written = fwrite(header->prog_name, sizeof(header->prog_name), 1, cor);
    if (bytes_written != 1) return EXIT_FAILURE; 
    write_int_big_end(cor, header->prog_size);
    bytes_written = fwrite(header->comment, sizeof(header->comment), 1, cor);
    if (bytes_written != 1) return EXIT_FAILURE; 

    free(header);

    return EXIT_SUCCESS;
}

int write_inst(FILE *cor, t_array *inst) 
{
    int i = 0;
    while (i < inst->size) {
        int len = my_strlen(inst->array[i]);
        size_t bytes_written = fwrite(inst->array[i], len, 1, cor);
        if (bytes_written != 1) return EXIT_FAILURE;
        free(inst->array[i]);
        i++;
    }

    free(inst);

    return EXIT_SUCCESS;
}

void write_int_big_end(FILE *cor, int num) {
    u_int8_t bytes[4];
    bytes[0] = (num >> 24) & 0xFF;
    bytes[1] = (num >> 16) & 0xFF;
    bytes[2] = (num >> 8) & 0xFF;
    bytes[3] = num & 0xFF;

    fwrite(bytes, sizeof(bytes), 1, cor);
}

void token_to_arg(t_arg_array **args, char *tok, int type) {
    (*args)->array[(*args)->count] = init_arg();
    t_arg *tmp = (*args)->array[(*args)->count];
    tmp->arg = init_str(my_strlen(tok) + 1);
    my_strcpy(tmp->arg, tok);
    tmp->type = type;
}
