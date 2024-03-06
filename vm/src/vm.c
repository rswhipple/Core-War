#include "op.h"
#include "vm_parse.h"
#include "core.h" 
#include "vm_execute.h"
#include "memory.h"

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
    core_t *core = init_core(head, flags); 

    // run game
    // game_loop(core);

    // memory cleanup
    cleanup(core);

    return 0;
}