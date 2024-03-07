#include "op.h"
#include "vm_parse.h"
#include "core.h" 
#include "game_loop.h"
#include "memory.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;   
    }
    
    flag_t *flags = init_flag();
    champion_t* head = parse_args(argc, argv, &flags);
    core_t *core = init_core(head, flags); 
    game_loop(core);
    cleanup(core);

    return 0;
}