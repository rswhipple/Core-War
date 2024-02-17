#include "../include/asm_parse.h"
#include "../include/helper.h"
#include "../include/memory.h"

int execute_asm(char *filename) {
    // init .cor file
    FILE *cor = create_cor_file(filename);

    // create header and instruction storage
    t_header *header = init_header();
    t_array *inst = init_t_array();

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

    while ((nread = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
        if (my_strncmp(line, ".name", 5) == 0) { 
            my_strcpy((*header)->prog_name, line + 7);
            int copied_len = my_strlen((*header)->prog_name);
            (*header)->prog_name[copied_len - 2] = '\0';
        }
        else if (my_strncmp(line, ".comment", 8) == 0) { 
            my_strcpy((*header)->comment, line + 10);
            int copied_len = my_strlen((*header)->comment);
             (*header)->comment[copied_len - 2] = '\0';
        } else if (my_strncmp(line, "/n", 1) == 0) {
            continue;
        }
        else {
            // read line
            // send line through assembler
            // save line into t_array
            // increment t_array size 
        }
    }
    
    return EXIT_SUCCESS;
}

FILE *create_cor_file(char *filename) {
    const char *write = "wb";
    FILE *cor= fopen(filename, write);
    return cor;
}

char *replace_ext(char *filename) {
    // TODO remove path if any
    int len = my_strlen(filename);
    char *new_ext = "cor";
    char *new_filename = init_str(len + 2);
    my_strncpy(new_filename, filename, len - 1);
    my_strcat(new_filename, new_ext);

    return new_filename;
}

void print_usage()
{
    // print usage instructions
    char *message = "USAGE\n\t./asm file_name[.s]\n";
    my_putstr(message);
}
