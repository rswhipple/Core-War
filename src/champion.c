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
    const char *read = "r";
    FILE *fp = fopen(filename, read);
    if (!fp) {
        return NULL;
    }

    champion_t *champ = init_champion(flags);
    read_file(&champ, fp);

    fclose(fp);

    return champ;
}

// create champion 
int read_file(champion_t **champ, FILE *fp) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
        if (my_strncmp(line, ".name", 5) == 0) { 
            my_strcpy((*champ)->champ_header->prog_name, line + 7);
            int copied_len = my_strlen((*champ)->champ_header->prog_name);
            (*champ)->champ_header->prog_name[copied_len - 2] = '\0';
        }
        else if (my_strncmp(line, ".comment", 8) == 0) { 
            my_strcpy((*champ)->champ_header->comment, line + 10);
            int copied_len = my_strlen((*champ)->champ_header->comment);
            (*champ)->champ_header->comment[copied_len - 2] = '\0';
        } else if (my_strncmp(line, "/n", 1) == 0) {
            continue;
        }
        // else {
        //     // send instruction through assembler
        //     // increment (*champ)->num_inst
        // }
    }
    
    return EXIT_SUCCESS;
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

// Print the contents of the 16 general purpose, ac, and carry flag registers
void print_champ_regs(champion_t *champ) {
	printf("-----Printing champion %d register contents-----\n", champ->id);
	for (int i = 0; i < REG_NUMBER; i++) {
		printf("register %d: %d\n", i + 1, champ->reg[i]);
	}
	printf("ac: %d\n", champ->ac);
	printf("carry: %d\n", champ->carry);
}

// create champion header
int read_file(champion_t **champ, FILE *fp) {
    // (*champ)->champ_header->magic = COREWAR_EXEC_MAGIC;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
    }
    
    return EXIT_SUCCESS;
}


// free champion
void free_champion(champion_t *champ) {
    free(champ->champ_header);
    free(champ);
}