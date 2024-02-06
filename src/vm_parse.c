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
#include "../include/helper.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"

flag_t *init_flag() {
    flag_t *flags = malloc(sizeof(flag_t));
    flags->num_champions = 0;
    flags->dump = -1;
    flags->id = 0;
    flags->address = 0;

    return flags;
}

// parse arguments
champion_t *parse_args(int argc, char **argv, flag_t** flags)
{
    int i = 1;
    champion_t *head = NULL;

    // read flags 
    while (i < argc ) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'n') {
                // set id
                (*flags)->id = my_atoi(argv[i + 1]);    // argv[i + 1] is the id
            } else if (argv[i][1] == 'a') {
                // set address
                (*flags)->address = my_atoi(argv[i + 1]);  // argv[i + 1] is the address
            } else if (argv[i][1] == 'd') {
                // set dump
                (*flags)->dump = my_atoi(argv[i + 1]);    // argv[i + 1] is the dump
            } else {
                print_usage();  // handles -h flag too
                break;
            }
            i += 2;     // increment i by 2
        } else {
            // create champion, adjust flags
                // TODO add error handling if champion isn't created
            if (head == NULL) {
                head = create_champion(*flags, argv[i]);
            } else {
                create_champion(*flags, argv[i]);
            }
            (*flags)->id = 0;
            (*flags)->address = 0;
            (*flags)->num_champions += 1;
        }
        i++;
    }

    return head;    // return head of champion linked list
}

void print_usage()
{
    // print usage instructions
}




