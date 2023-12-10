#include <stddef.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#include "rom.h"
#include "types.h"
#include "cpu.h"

#define FONT_SIZE 10
#define RAM_SIZE 64*1024    // 64 kb

void printRamContent(unsigned char* ram, size_t ini, size_t end)
{
    for(size_t i=ini; i<end; ++i) {
        printf("%02x ", ram[i]);
        if ((i+1)%8==0) printf(" ");
        if ((i+1)%16==0) printf("\n");
    }
    printf("\n");
}

int main(void) {
    CPU cpu;
    cpu_init(&cpu);
    unsigned char ram[RAM_SIZE];

    loadRom("data/test.nes", ram);
    
    // seta reset vector para o endereço de entrada do programa
    ram[0xEE] = 0xAA;
    ram[0xFFFC] = 0x00;
    ram[0xFFFD] = 0x80;
    // pega, do reset vector, o endereço de entrada do programa 
    cpu.PC = (ram[0xFFFD] << 8) + ram[0xFFFC];

    printRamContent(ram, 0x8000, 0x8010);

    execute_next_instruction(&cpu, ram);
    execute_next_instruction(&cpu, ram);

    
    return 0;





    InitWindow(800, 600, "Nesm");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            char text[50] = {'\0'};
            sprintf(text, "A: %02x\nX: %02x\nY: %02x\n", cpu.A, cpu.X, cpu.Y);
            DrawText(text, 10, 20, FONT_SIZE, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
