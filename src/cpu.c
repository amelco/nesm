#include <stdio.h>

#include "cpu.h"
#include "types.h"
#include "types.h"

// https://www.nesdev.org/wiki/CPU_power_up_state
void cpu_init(CPU* cpu){
    cpu->PC = 0;
    cpu->S = 0xFF;
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->P = 0b00000000;
}

void cpu_reset(CPU* cpu){
    cpu->S -= 3;
    cpu->P = 0b00000000;
}

// https://www.masswerk.at/6502/6502_instruction_set.html
void execute_next_instruction(CPU* cpu, unsigned char* ram) {
    // printf("PC: %04x\n", cpu->PC);
    unsigned char op = ram[cpu->PC];
    cpu->PC++;
    unsigned short cycles = 0;

    switch (op) {
    case LDA_IMM:
    {
        cycles = 2;
        cpu->A = ram[cpu->PC];
        cpu->PC++;
        if (cpu->A == 0) set_zero(cpu->P);
        if (get_negative(cpu->A) == 1) set_negative(cpu->P);
        break;
    }
    case LDA_ZRP:
    {
        cycles = 3;
        unsigned char addr = ram[cpu->PC];
        cpu->PC++;
        cpu->A = ram[addr];
        if (cpu->A == 0) set_zero(cpu->P);
        if (get_negative(cpu->A) == 1) set_negative(cpu->P);
        break;
    }
    case LDA_ZPX:
    {
        cycles = 3;
        unsigned char addr = ram[(cpu->PC) + (cpu->X)];
        cpu->PC++;
        cpu->A = ram[addr];
        if (cpu->A == 0) set_zero(cpu->P);
        if (get_negative(cpu->A) == 1) set_negative(cpu->P);
        break;
    }
        case JSR:
    {
        cycles = 6;
        push_stack(cpu, ram);
        unsigned char lowNewPC  = {ram[cpu->PC++]};
        unsigned char highNewPC = {ram[cpu->PC++]};
        cpu->PC = lowNewPC + (highNewPC << 8);
        break;
    }
    default:    // Unkown instruction
        printf("ERROR: op_code '%02x' not implemented.\n", op);
    }

    print_registers(cpu);

    //  emulation of processing time
    while (cycles > 0)  cycles--;


}

void print_registers(CPU* cpu){
    printf(" A:   %02X\n", cpu->A);
    printf("PC: %04X\n", cpu->PC);
    printf(" P: %08b\n", cpu->P);
}
