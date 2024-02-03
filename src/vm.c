#include "../include/op.h"
#include "../include/vm_parse.h"

int main(int argc, char **argv)
{
    // parse arguments
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;
    }
    
    flag_t flags = init_flag();
    parse_args(argc, argv, &flags);

    // init and run core
    core_t *core = NULL;

    // print winner

    return 0;
}