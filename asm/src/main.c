#include "../include/asm.h"
#include "../include/asm_parse.h"
#include "../include/helper.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;  
    }

    int i = 1;
    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'h') {   // handle flag
            print_usage();
        }
        else {
            if ((execute_asm(argv[i]))) {      // assemble file
                char *error = "execution was not completed.\n";
                my_puterror(error);
                return EXIT_FAILURE;
            }
        }
        i++;
    }

    return EXIT_SUCCESS;
}

void print_usage()
{
    char *message = "USAGE\n\t./asm file_name[.s]\nDESCRIPTION\n\tfile_name file in assembly language to be converted into file_name.cor, an executable in the Virtual Machine.\n";
    my_putstr(message);
}
