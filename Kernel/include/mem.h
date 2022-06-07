#ifndef _MEM_H
#define _MEM_H

#include <stdint.h>
#include <naiveConsole.h>
#include <lib.h>

#define REGISTERS_COUNT 16

void saveReg(uint64_t * regs);
void printMemory(uint64_t argument);
void getRegistersInfo();

#endif