#include "../include/op.h"
#include "../include/vm_parse.h"
#include "../include/core.h" 
#include "../include/memory.h"

int main(int argc, char **argv)
{
    // parse arguments
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;  
    }
    
    flag_t *flags = init_flag();
    champion_t* head = parse_args(argc, argv, &flags);

    // init core, load champs, run core
    core_t *core = init_core(flags);

    // print winner

    // memory cleanup
    cleanup(head, core);

    return 0;
}