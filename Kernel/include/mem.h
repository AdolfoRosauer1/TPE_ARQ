#ifndef _MEM_H
#define _MEM_H

#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>

#define REGISTERS_COUNT 16
#define SIZE 32

void saveReg(uint64_t * regs);
void printMemory(uint64_t mode, uint64_t sc, uint64_t start);
void getRegistersInfo( uint64_t mode , uint64_t sc);

#endif