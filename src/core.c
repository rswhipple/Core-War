#include "../include/op.h"    // op_t

// function pointers
void execute(core_t *c);
void fetch(core_t *c);

core_t *init_c(u64 *memory, u64 max_mem)
{
    core_t *c = (core_t *)malloc(sizeof(core_t));         // allocate memory for cpu

}

void free_core(core_t *c)
{
    free(c);
}

void run_core(core_t *c)
{
    while (c->inst != OP_NB) {
        fetch(c);
        execute(c);
    }
}

void fetch(core_t *c)
{
    c->ac++;
    c->inst = c->mem[c->ac] & FIRST_BYTE;       // get first byte of instruction
}

void execute(core_t *c)
{
    switch (c->inst) {
        case OP_LIVE:
            break;
    }
}

