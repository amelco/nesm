#ifndef ROM_H
#define ROM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned char* data;
    size_t size;
} ROM;

ROM* loadRom(char* filePath);
void printRomContent(ROM* rom);
void closeRom(ROM* rom);

#endif //ROM_H
