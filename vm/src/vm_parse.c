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
    // TODO: the option handlier is still having segv issues, fix in the following lines
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
                // TODO: add error handling if champion isn't created
            if (head == NULL) {
                head = create_champ(*flags, argv[i]);
            } else {
                champion_t *temp = head; 
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = create_champ(*flags, argv[i]);
            }
            (*flags)->id = 0;
            (*flags)->address = 0;
            (*flags)->num_champions += 1;
        }
        i++;
    }
    print_champions(head);
    return head;    // return head of champion linked list
}

void print_usage()
{
    // print usage instructions
}




