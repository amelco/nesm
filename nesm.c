#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

#include "cpu.h"
#include "rom.h"

#define FONT_SIZE 20

int main(void) {
    Rom* rom = loadRom("data/all_instrs.nes");
    // printRomContent(rom);

    CPU cpu;
    cpu_init(&cpu, rom);

    InitWindow(800, 600, "Nesm");
    SetTargetFPS(60);
    Font font = LoadFontEx("./resources/fonts/Alegreya-Regular.ttf", FONT_SIZE, NULL, 0);
    while (!WindowShouldClose()) {
        char text[50] = {'\0'};
        sprintf(text, "A = %d", cpu.A);

        BeginDrawing();
        {
            Vector2 pos = {10, 20};
            DrawTextEx(font, text, pos, FONT_SIZE, 0, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    closeRom(rom);

    return 0;
}
