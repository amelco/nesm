#ifndef CPU_H
#define CPU_H

#include "types.h"

typedef struct {
    Word PC;
    Byte S;
    Byte A;
    Byte X;
    Byte Y;
    Byte P;
} CPU;

void LDA(unsigned char* data, ...);
void print_registers(CPU* cpu);
void cpu_init(CPU* cpu);
void cpu_reset(CPU* cpu);
void execute_next_instruction(CPU* cpu, unsigned char* ram);

#endif //CPU_H
