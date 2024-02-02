#include "../include/op.h"
#include "../include/champion.h"
#include <sys/fcntl.h>

void free_champion(champion_t *champ) {

}

// initialize champion
champion_t *init_champion(void) {
    champion_t *new_champ = malloc(sizeof(champion_t));
    if (new_champ == NULL) {
        return NULL;
    }
    new_champ->champ_header = NULL;
    new_champ->id = 0;
    new_champ->num_instuctions = 0;
    new_champ->instructions = NULL;
    for (int i = 0; i < 16; i++) {
        new_champ->registers[i] = 0;
    }
    new_champ->pc = new_champ->registers[14];
    new_champ->carry = new_champ->registers[15];
    new_champ->next = NULL;

    new_champ->free_champion = free_champion;
    return new_champ;
}

int create_champion(champion_t *champ, char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return -1;
    }

    champ->champ_header = get_header(fd); 
    champ->instructions = get_instructions(filename, fd);

    close(fd);

    return 0;
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
    while (getline(header->prog_name, COMMENT_LENGTH, fd) != )
    // TODO read header from file

    return header;
}

// create champion instructions
op_t *get_instructions(char *filename, int fd) {
    op_t *new_instructions = malloc(sizeof(op_t));
    if (new_instructions == NULL) {
        return NULL;
    }

    // TODO read instructions from file

    return new_instructions;
}

// free champion