#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "rom.h"
#include "ram.h"

typedef struct {
    Word PC;
    Byte S;
    Byte A;
    Byte X;
    Byte Y;
    Byte P;
} CPU;

void print_registers(CPU* cpu);
void cpu_init(CPU* cpu);
void cpu_reset(CPU* cpu);
void execute_next_instruction(CPU* cpu, ROM* rom, RAM* ram);

#endif //CPU_H
