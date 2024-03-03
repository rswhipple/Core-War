#include "../include/op.h"
#include "../include/helper.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"
#include "../include/memory.h"
#include <sys/fcntl.h>


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

    champ->inst = NULL;  // TODO work on this 
    for (int i = 0; i < 16; i++) {
        champ->reg[i] = 0;
    }
    champ->ac = 0;
    champ->carry = 0;
    champ->next = NULL;

    return champ;
}

// parse champion data
int read_file(champion_t **champ, int fd) {
    // read header
    ssize_t bytes;
    u_int8_t byte;
    bytes = read(fd, (*champ)->champ_header, sizeof(header_t)); // TODO: add error check
    print_header((*champ)->champ_header);   // TESTING print header

    // read instruction data
    size_t prog_size = (size_t)(*champ)->champ_header->prog_size;
    u_int8_t buf[prog_size];
    memset(buf, 0, prog_size);
    bytes = read(fd, &buf, prog_size);
    print_inst_buf((*champ)->champ_header, buf, prog_size); // TESTING Print contents of buf

    // Convert instruction data to inst_array
    convert_to_inst(buf, prog_size);

    return EXIT_SUCCESS;
}

int convert_to_inst(u_int8_t *buf, size_t prog_size) {

    return EXIT_SUCCESS;
}

// Print the contents of the 16 general purpose, ac, and carry flag registers
void print_header(header_t *header) {
	printf("-----Printing champion \"%s\" header contents-----\n", header->prog_name);
	printf("magic: %i\n", header->magic);
    printf("prog_size: %i\n", header->prog_size);
	printf("comment: %s\n", header->comment);
}

// Print the inst buf hex by hex
void print_inst_buf(header_t *header, u_int8_t *buf, size_t size) {
	printf("-----Printing champion \"%s\" instruction raw data-----\n", header->prog_name);

    // Print the contents of the buffer
    for(u_int8_t i = 0; i < size; i++) {
        printf("buf[%hhu] = %02x\n", i, buf[i]);
    }
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
        curr = curr->next;
    }
}
