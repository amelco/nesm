#include <stdio.h>
#include <stdlib.h>
#include "rom.h"

void readRom(FILE* fd, unsigned char* ram) {
    for (size_t i=0x8000; i<0xFFFF; ++i)
    {
        unsigned char c = fgetc(fd);
        ram[i] = c;
    }
    fclose(fd);
}

// Load rom file into ram starting from 0x8000
void loadRom(char* filePath, unsigned char* ram) {
    FILE* fd = fopen(filePath, "rb");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }
    readRom(fd, ram);
}
