#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#include "cpu.h"
#include "rom.h"
#include "ram.h"

#define FONT_SIZE 10

int main(void) {
    ROM* rom = loadRom("data/all_instrs.nes");
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
    
    print_registers(&cpu);
    execute_next_instruction(&cpu, rom, &ram);
    print_registers(&cpu);
    execute_next_instruction(&cpu, rom, &ram);
    print_registers(&cpu);
    execute_next_instruction(&cpu, rom, &ram);

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
