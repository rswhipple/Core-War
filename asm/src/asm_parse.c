#include "../include/asm_parse.h"
#include "../include/helper.h"

int execute_asm(char *filename) {
    // init .cor file
    int fd = create_cor_file(filename);

    // open, read and transform .S file
    const char *read = "r";
    FILE *fp = fopen(filename, read);
    if (!fp) {
        return EXIT_FAILURE;
    }
    
    read_file(fp);

    // close streams
    fclose(fp);
    close(fd);

    return EXIT_SUCCESS;
}

int read_file(FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
        if (my_strncmp(line, ".name", 5) == 0) { 
            // my_strcpy((*champ)->champ_header->prog_name, line + 7);
            // int copied_len = my_strlen((*champ)->champ_header->prog_name);
            // (*champ)->champ_header->prog_name[copied_len - 2] = '\0';
        }
        else if (my_strncmp(line, ".comment", 8) == 0) { 
            // my_strcpy((*champ)->champ_header->comment, line + 10);
            // int copied_len = my_strlen((*champ)->champ_header->comment);
            // (*champ)->champ_header->comment[copied_len - 2] = '\0';
        } else if (my_strncmp(line, "/n", 1) == 0) {
            continue;
        }
        // else {
        //     // send instruction through assembler
        //     // increment (*champ)->num_inst
        // }
    }
    
    return EXIT_SUCCESS;
}

int create_cor_file(char *filename) {

}

char *replace_ext(char *filename) {
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
}
