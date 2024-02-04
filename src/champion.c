#include "../include/op.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"
#include <sys/fcntl.h>

void free_champion(champion_t *champ) {

}

// initialize champion
champion_t *init_champion(flag_t *flags) {
    champion_t *champ = malloc(sizeof(champion_t));
    if (champ == NULL) {
        return NULL;
    }
    champ->champ_header = NULL;
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
        return -1;
    }

    champion_t *champ = init_champion(flags);
    champ->champ_header = get_header(fd); 
    champ->inst = get_instructions(champ->champ_header, fd);

    close(fd);

    return champ;
}

// create champion header
header_t *get_header(int fd) {
    header_t *header = malloc(sizeof(header_t));
    if (header == NULL) {
        return NULL;
    }
    header->magic = COREWAR_EXEC_MAGIC;
    header->prog_size = 0;
    getline(header->prog_name, PROG_NAME_LENGTH, fd);
    // buf for comment
    // while (getline(header->prog_name, COMMENT_LENGTH, fd) != )
    // TODO read header from file

    return header;
}

// create champion instructions
op_t *get_instructions(champion_t *champ, int fd) {
    op_t *new_instructions = malloc(sizeof(op_t));
    if (new_instructions == NULL) {
        return NULL;
    }

    // TODO read instructions from file
    ssize_t bytes = 0;
    char *buf = init_str(IDX_MOD);
    while ((bytes = getline(buf, IDX_MOD, fd)) != -1) {

    }

    return new_instructions;
}

// free champion