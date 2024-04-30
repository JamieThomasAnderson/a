#ifndef a_block
#define a_block

#include "common.h"

#define GROW 1.5
#define SIZE 8

typedef struct {
    int length;
    int capacity;
    uint8_t* code;
} Block;

typedef enum {
    OP_RETURN
} OpCode;

void newBlock(Block* block);
void writeBlock(Block* block, uint8_t byte);

#endif