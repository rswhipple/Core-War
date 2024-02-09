#include "../include/op.h"
#include "../include/helper.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"
#include "../include/memory.h"
#include <sys/fcntl.h>


// initialize champion
champion_t *init_champion(flag_t *flags) {
    champion_t *champ = malloc(sizeof(champion_t));
    if (champ == NULL) { return NULL; }

    champ->champ_header = malloc(sizeof(header_t));
    if (champ->champ_header == NULL) { return NULL; }
    champ->champ_header->magic = COREWAR_EXEC_MAGIC;

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

    return champ;
}

champion_t *create_champion(flag_t *flags, char *filename) {
    int fd = open(filename, O_RDONLY, 0644);
    if (!fd) {
        return NULL;
    }

    champion_t *champ = init_champion(flags);

    read_file(&champ, fd);

    close(fd);

    return champ;
}

// create champion 
int read_file(champion_t **champ, int fd) {
    ssize_t bytes;
    // Read header 
    bytes = read(fd, (*champ)->champ_header, sizeof(header_t));

    while (bytes > 0) 
    {
        // Read instructions
    }
    
    return EXIT_SUCCESS;
}

// Print the contents of the 16 general purpose, ac, and carry flag registers
void print_champ_regs(champion_t *champ) {
	printf("-----Printing champion %d register contents-----\n", champ->id);
	for (int i = 0; i < REG_NUMBER; i++) {
		printf("register %d: %d\n", i + 1, champ->reg[i]);
	}
	printf("ac: %d\n", champ->ac);
	printf("carry: %d\n", champ->carry);
}

// print champion
void print_champions(champion_t *head) {
    champion_t *curr = head;
    while (curr) {
        // print
        printf("\nChamp id number %i is named %s\n", curr->id, curr->champ_header->prog_name);
        printf("Comment: %s\n", curr->champ_header->comment);
        curr = curr->next;
    }
}
