#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra -ggdb -lraylib"
LIBS="-L/usr/local/lib"

mkdir -p build
#gcc -Wall -Wextra cpu.c nesm.c -o build/nesm
clang $CFLAGS -o ./build/nesm ./src/cpu.c ./src/rom.c ./src/nesm.c $LIBS
