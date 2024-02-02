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

void print_usage()
{
    // print usage instructions
}

// parse arguments
int parse_args(int argc, char **argv)
{
    int num_champions = 0;
    int i = 1;
    while (i < argc) {
        // initialize a new champion
        
        // read flags 
        champion_t *new_champ = init_champion();
        while (i < argc ) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == 'n') {
                    // set id
                    // argv[i + 1] is the id
                } else if (argv[i][1] == 'a') {
                    // set address
                    // argv[i + 1] is the address
                } else if (argv[i][1] == 'd') {
                    // set dump
                    // argv[i + 1] is the dump
                } else {
                    print_usage();
                    break;
                }
                // increment i by 2
            } else {
                // parse file and store in champion
                // argv[i] is the file
                break;
            }
        }
        i++;
    }

    return num_champions;
}



