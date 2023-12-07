#ifndef ROM_H
#define ROM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned char* data;
    size_t size;
} Rom;

Rom* loadRom(char* filePath);
void printRomContent(Rom* rom);
void closeRom(Rom* rom);

#endif //ROM_H
