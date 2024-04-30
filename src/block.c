#include <stdlib.h>
#include <stdio.h>

#include "block.h"

void newBlock(Block* block)
{
    block->length = 0;
    block->capacity = 0;
    block->code = NULL;
}

void* expandBlock(void* pointer, size_t oldLength, size_t newLength)
{
    if (newLength == 0)
    {
        free(pointer);
        return NULL;
    }

    void* block = realloc(pointer, newLength);
    return block;
}

void writeBlock(Block* block, uint8_t byte)
{
    if (block->capacity < block->length + 1)
    {
        expandBlock(block);
    }

    printf("%d", block->capacity);
    printf("%d", block->length);

    // block->code[block->length] = byte;
    // block->length++;
}