#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <naiveConsole.h>
#include <stdint.h>
#include <mem.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXCEPTION_ID 6
#define IP_INDEX 15
#define SP_INDEX 18

extern uint64_t getSP();
extern void saveRegisterInfo();
void exceptionDispatcher(int exception, uint64_t *registers);
void zeroDivision();
void invalidOpcode();
void saveInitialState(uint64_t IP, uint64_t SP);
void resetTerminal(uint64_t *registers);

typedef struct initialState{
    uint64_t IP;
    uint64_t SP;
}initialState;

#endif