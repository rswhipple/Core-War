/*
USAGE
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address]
[prog_name] ...

DESCRIPTION
-dump nbr_cycle
dumps the memory after the nbr_cycle execution (if the round isn’t
already over) with the following format: 32 bytes/line in
hexadecimal (A0BCDEFE1DD3...)

-n prog_number
sets the next program’s number. By default, the first free number
in the parameter order

-a load_address
sets the next program’s loading address. When no address is
specified, optimize the addresses so that the processes are as
far away from each other as possible. The addresses are MEM_SIZE
modulo

*/

#include "../include/op.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"

void print_usage()
{
    // print usage instructions
}

flag_t init_flag() {
    flag_t flags;
    flags.num_champions = 0;
    flags.dump = 0;
    flags.id = 0;
    flags.address = 0;
}

// parse arguments
int parse_args(int argc, char **argv)
{
    int i = 1;
    flag_t flags = init_flag();

    while (i < argc) {
        // read flags 
        while (i < argc ) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == 'n') {
                    // set id
                    flags.id = my_atoi(argv[i + 1]);    // argv[i + 1] is the id
                } else if (argv[i][1] == 'a') {
                    // set address
                    flags.address = my_atoi(argv[i + 1]);  // argv[i + 1] is the address
                } else if (argv[i][1] == 'd') {
                    // set dump
                    flags.dump = my_atoi(argv[i + 1]);    // argv[i + 1] is the dump
                } else {
                    print_usage();
                    break;
                }
                i += 2;     // increment i by 2
            } else {
                // parse file, create champion, 
                create_champion(&flags, argv[i]);
                break;
            }
        }
        i++;
    }

    return flags.num_champions;
}



