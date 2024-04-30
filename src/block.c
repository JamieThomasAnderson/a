#include <stdlib.h>
#include <stdio.h>

#include "block.h"

void newBlock(Block* block)
{
    block->length = 0;
    block->capacity = 0;
    block->code = NULL;
}

void* expandBlock(void* pointer, size_t oldLength)
{

    int newLength = oldLength < SIZE ? SIZE : SIZE * GROW;

    void* block = realloc(pointer, newLength);
    return block;
}

void writeBlock(Block* block, uint8_t byte)
{
    if (block->capacity < block->length + 1)
    {
        expandBlock(block, sizeof(type(byte)) * block->length);
    }

    printf("%d", block->capacity);
    printf("%d", block->length);

    // block->code[block->length] = byte;
    // block->length++;
}