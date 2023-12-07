#include "rom.h"

Rom* readRom(FILE* fd)
{
    Rom* rom = malloc(sizeof(Rom));

    fseek(fd, 0, SEEK_END);
    rom->size = ftell(fd);
    rom->data = malloc(rom->size * sizeof(unsigned char));

    fseek(fd, 0, SEEK_SET);
    for (size_t i=0; i<rom->size; ++i)
    {
        unsigned char c = fgetc(fd);
        rom->data[i] = c;
    }
    fclose(fd);

    return rom;
}

Rom* loadRom(char* filePath)
{
    FILE* fd = fopen(filePath, "rb");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }
    return readRom(fd);
}

void printRomContent(Rom* rom)
{
    for(size_t i=0; i<rom->size; ++i) {
        printf("%02x ", rom->data[i]);
        if ((i+1)%8==0) printf(" ");
        if ((i+1)%16==0) printf("\n");
    }
    printf("\n");
}

void closeRom(Rom* rom)
{
    free(rom->data);
}

