#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

#define PROMPT_SIZE 5
#define DEFAULT_COLOR 0x0F
#define LINE_LENGTH width*2


void ncPrint(const char * string);
void ncPrintChar(char character);
void ncBackSpace();
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();

#endif