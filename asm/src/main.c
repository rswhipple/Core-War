#include "../include/asm.h"
#include "../include/asm_parse.h"

int main(int argc, char **argv)
{
    // parse arguments
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;  
    }

    int i = 1;
    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'h') {
            print_usage();
        }
        else {
            if (!(execute_asm(argv[i]))) {
                char *error = "execution was not completed.\n";
                my_puterror(error);
                return EXIT_FAILURE;
            }
        }
        i++;
    }

    return EXIT_SUCCESS;
}