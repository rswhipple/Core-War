#include "../include/asm_parse.h"
#include "../include/helper.h"
#include "../include/memory.h"

int execute_asm(char *filename) {
    // init .cor file
    FILE *cor = create_cor_file(filename);

    // create header and instruction storage
    t_header *header = init_header();
    t_array *inst = init_t_array(MAX_INSTRUCTIONS);

    // open, read and transform .S file
    const char *read = "r";
    FILE *fp = fopen(filename, read);
    if (!fp) return EXIT_FAILURE;
    
    read_file(fp, &header, &inst);
    fclose(fp);

    // write file
    if (write_header(cor, header)) return EXIT_FAILURE;
    if (write_inst(cor, inst)) return EXIT_FAILURE;
    fclose(cor);

    return EXIT_SUCCESS;
}

int read_file(FILE *fp, t_header **header, t_array **inst) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    // t_array *dict = init();  // I don't think I need this

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
            char *token = convert_inst(line);
            (*inst)->array[(*inst)->size] = init_str(my_strlen(token) + 1);    
            my_strcpy((*inst)->array[(*inst)->size++], token);
        }
    }

    // free_dict(dict);
    
    return EXIT_SUCCESS;
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

void print_usage()
{
    char *message = "USAGE\n\t./asm file_name[.s]\nDESCRIPTION\n\tfile_name file in assembly language to be converted into file_name.cor, an executable in the Virtual Machine.\n";
    my_putstr(message);
}
