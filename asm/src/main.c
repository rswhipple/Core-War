#include "../include/asm.h"

int main(int argc, char **argv)
{
    // parse arguments
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;  
    }

    int i, success = 1;
    while (argv[i]) {
        if (!(success = create_cor_file(argv[i]))) return EXIT_FAILURE;
        i++;
    }

    return EXIT_SUCCESS;
}