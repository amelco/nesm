#include <stdio.h>
#include "cpu.h"
#include "types.h"
#include "types.h"

#define push_stack(cpu,ram)\
    ram[cpu->S--] = cpu->PC & 0x00FF;\
    ram[cpu->S--] = (cpu->PC & 0xFF00) >> 8

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

void execute_next_instruction(CPU* cpu, unsigned char* ram) {
    unsigned char op = ram[cpu->PC++];
    unsigned short num_cycles = 0;
    unsigned short num_bytes = 0;   // numero de bytes dos "argumentos"
    (void)num_cycles;
    (void)num_bytes;

    switch (op) {
    case 0xA9:  // LDA immediate mode
        num_cycles = 2;
        num_bytes = 1;
        cpu->A = ram[cpu->PC++];
        break;
    case 0x20:  // JSR
        num_cycles = 6;
        num_bytes = 2;
        push_stack(cpu, ram);
        unsigned char lowNewPC  = {ram[cpu->PC++]};
        unsigned char highNewPC = {ram[cpu->PC++]};
        cpu->PC = lowNewPC + (highNewPC << 8);
        break;
    default:    // Unkown instruction
        printf("ERROR: op_code '%02x' not implemented.", op);
    }
}

void print_registers(CPU* cpu){
    printf("PC: %04x\n", cpu->PC);
    printf("A: %02x\n", cpu->A);
}
