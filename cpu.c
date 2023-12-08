#include <stdio.h>
#include "cpu.h"
#include "ram.h"
#include "types.h"
#include "types.h"

#define push_stack(cpu,ram)\
    ram->data[cpu->S--] = cpu->PC & 0x00FF;\
    ram->data[cpu->S--] = (cpu->PC & 0xFF00) >> 8

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

void execute_next_instruction(CPU* cpu, ROM* rom, RAM* ram) {
    unsigned char op = rom->data[cpu->PC++];
    unsigned short num_cycles = 0;
    unsigned short num_bytes = 0;   // numero de bytes dos "argumentos"
    (void)num_cycles;
    (void)num_bytes;

    switch (op) {
    case 0xA9: // LDA immediate mode
        num_cycles = 2;
        num_bytes = 1;
        cpu->A = rom->data[cpu->PC++];
        break;
    case 0x20:
        num_cycles = 6;
        num_bytes = 2;
        push_stack(cpu, ram);
        unsigned char lowNewPC  = {rom->data[cpu->PC++]};
        unsigned char highNewPC = {rom->data[cpu->PC++]};
        cpu->PC = lowNewPC + (highNewPC << 8);
        break;
    default:
        printf("ERROR: op_code '%02x' not implemented.", op);
        exit(1);
    }
}

void print_registers(CPU* cpu){
    printf("PC: %04x\n", cpu->PC);
    printf("A: %02x\n", cpu->A);
}
