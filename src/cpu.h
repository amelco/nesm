#ifndef CPU_H
#define CPU_H

#include "types.h"

#define push_stack(cpu,ram)\
    ram[cpu->S--] =  cpu->PC & 0x00FF;\
    ram[cpu->S--] = (cpu->PC & 0xFF00) >> 8

#define set_bit(byte, pos)   byte |= 1 << pos
#define get_bit(byte, pos) ((byte & (1 << pos)) != 0)
#define set_carry(byte)      set_bit(byte, 0)
#define set_zero(byte)       set_bit(byte, 1)
#define set_interrupt(byte)  set_bit(byte, 2)
#define set_decimal(byte)    set_bit(byte, 3)
#define set_overflow(byte)   set_bit(byte, 6)
#define set_negative(byte)   set_bit(byte, 7)
#define get_carry(byte)      get_bit(byte, 0)
#define get_zero(byte)       get_bit(byte, 1)
#define get_interrupt(byte)  get_bit(byte, 2)
#define get_decimal(byte)    get_bit(byte, 3)
#define get_overflow(byte)   get_bit(byte, 6)
#define get_negative(byte)   get_bit(byte, 7)

#define LDA_IMM 0xA9
#define LDA_ZRP 0xA5
#define LDA_ZPX 0xB5
#define JSR     0x20

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
