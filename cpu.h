#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "rom.h"

typedef struct {
    Word PC;
    Byte SP;
    Byte A;
    Byte X;
    Byte Y;
    Byte PS;

    Rom* rom;
} CPU;

void cpu_init(CPU *cpu, Rom* rom);


#endif //CPU_H
