#include "../include/op.h"
#include "../include/helper.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"
#include <sys/fcntl.h>


// initialize champion
champion_t *init_champion(flag_t *flags) {
    champion_t *champ = malloc(sizeof(champion_t));
    if (champ == NULL) { return NULL; }

    champ->champ_header = malloc(sizeof(header_t));
    if (champ->champ_header == NULL) { return NULL; }

    // set id 
    if (flags->id) { champ->id = flags->id; } 
    else { champ->id = flags->num_champions + 1; }

    if (flags->address) { champ->address = flags->address; }
    else { champ->address = 0; }

    champ->num_inst = 0;
    champ->inst = NULL;
    for (int i = 0; i < 16; i++) {
        champ->reg[i] = 0;
    }
    champ->ac = 0;
    champ->carry = 0;
    champ->next = NULL;

    champ->free_champion = free_champion;
    return champ;
}

champion_t *create_champion(flag_t *flags, char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }

    champion_t *champ = init_champion(flags);
    int success = read_file(&champ, fd);

    close(fd);

    return champ;
}

// create champion header
// int read_file(champion_t **champ, int fd) {
//     // (*champ)->champ_header->magic = COREWAR_EXEC_MAGIC;

//     ssize_t bytes = 0;
//     char *buf = init_str(BUF_SIZE);
//     while ((bytes = getline(buf, BUF_SIZE, fd)) != -1) {

//     }

//     return EXIT_SUCCESS;
// }


// free champion
void free_champion(champion_t *champ) {

}