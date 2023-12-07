#include "cpu.h"
#include "rom.h"

void cpu_init(CPU *cpu, Rom* rom){
    cpu->PC = 0xFFCE;
    cpu->SP = 0xFF;
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->PS = 0b00000000;
    cpu->rom = rom;
}
