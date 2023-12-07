#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#include "cpu.h"
#include "rom.h"

#define FONT_SIZE 10

typedef struct {
    unsigned char data[RAMSIZE];
} RAM;


int main(void) {
    Rom* rom = loadRom("data/all_instrs.nes");
    // printRomContent(rom);

    CPU cpu;
    RAM ram;
    cpu_init(&cpu);
    print_registers(&cpu);

    // seta reset vector para o endereço de entrada do programa
    ram.data[0xFFFC] = 0x80;
    ram.data[0xFFFD] = 0x25;
    // pega, do reset vector, o endereço de entrada do programa 
    cpu.PC = (ram.data[0xFFFD] << 8) + ram.data[0xFFFC];
    
    unsigned char op = exec_next_instruction(&cpu, rom);
    switch (op) {
    case 0xA9: // LDA immediate mode
        cpu.A = exec_next_instruction(&cpu, rom);
        break;
    }
    print_registers(&cpu);

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
    closeRom(rom);

    return 0;
}
