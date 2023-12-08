#ifndef RAM_H
#define RAM_H

#define RAMSIZE 0xFFFF

typedef struct {
    unsigned char data[RAMSIZE];
} RAM;

#endif //RAM_H
