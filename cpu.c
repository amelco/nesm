#include <stdio.h>
#include "cpu.h"
#include "types.h"

// https://www.nesdev.org/wiki/CPU_power_up_state
void cpu_init(CPU* cpu){
    cpu->PC = 0;
    cpu->S = 0xFF;
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->P = 0b00100010;
}

void cpu_reset(CPU* cpu){
    cpu->S -= 3;
    cpu->P = 0b00100010;
}

unsigned char exec_next_instruction(CPU* cpu, Rom* rom)
{
    return rom->data[cpu->PC++];
}

void print_registers(CPU* cpu){
    printf("PC: %04x\n", cpu->PC);
    printf("A: %02x\n", cpu->A);
}
