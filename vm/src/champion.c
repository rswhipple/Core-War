#include "../include/op.h"
#include "../include/helper.h"
#include "../include/champion.h"
#include "../include/vm_parse.h"
#include "../include/memory.h"
#include <sys/fcntl.h>


champion_t *create_champ(flag_t *flags, char *filename) {
    int fd = open(filename, O_RDONLY, 0644);
    if (!fd) {
        return NULL;
    }

    champion_t *champ = init_champion(flags);

    read_file(&champ, fd);

    close(fd);

    return champ;
}

champion_t *init_champion(flag_t *flags)  {
    champion_t *champ = malloc(sizeof(champion_t));
    if (champ == NULL) { return NULL; }

    champ->name = NULL;
    champ->comment = NULL;
    champ->string = NULL;
    champ->id = 0;
    champ->cursor = init_cursor(flags);
    champ->next = NULL;

    return champ;
}

// initialize champion
cursor_t *init_cursor(flag_t *flags) {
    cursor_t *cursor = malloc(sizeof(cursor_t));
    if (cursor == NULL) { return NULL; }

    // set id 
    if (flags->id) { cursor->id = flags->id; } 
    else { cursor->id = flags->num_champions + 1; }

    if (flags->address) { cursor->index_start = flags->address; }
    else { cursor->index_start = 0; }

    for (int i = 0; i < 16; i++) {
        cursor->reg[i] = 0;
    }
    cursor->ac = 0;
    cursor->carry = 0;
    cursor->next = NULL;

    return cursor;
}

// parse champion data
int read_file(champion_t **champ, int fd) {
    // read header
    ssize_t bytes;
    header_t *header = malloc(sizeof(header_t));
    bytes = read(fd, header, sizeof(header_t)); 
    /* TODO: add MAGIC check */ 

    (*champ)->name = init_and_strncpy(header->prog_name);
    (*champ)->comment = init_and_strncpy(header->comment);
    int prog_size = header->prog_size;

    print_header(header);   // TESTING print header

    // read instruction data
    char buf[prog_size];
    memset(buf, 0, prog_size);
    bytes = read(fd, &buf, sizeof(char) * prog_size);
    (*champ)->string = buf;

    print_inst_buf(header, buf, prog_size);   // TESTING print buf

    free(header);

    return EXIT_SUCCESS;
}
