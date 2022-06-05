#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

#define PROMPT_SIZE 5
#define DEFAULT_COLOR 0x0F
#define LINE_LENGTH width*2
#define LAST_LINE video + (width*height*2) - LINE_LENGTH

typedef struct screen
{
    uint8_t * current;
    uint32_t width;
    uint32_t height;
    uint32_t offset;
}screen;

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void ncPrint(const char * string);
void ncPrintChar(char character);
void ncBackSpace();
void ncNewline();
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear();

//   left/right console methods

void ncStartMulti();
uint32_t line_length( int sc );
uint8_t * last_line( int sc );
int is_in_screen(int sc, int index );
int is_divide_line( uint32_t index );
void ncScrollMulti( int sc );
void ncNewlineMulti( int sc );
void ncBackspaceMulti( int sc );
void ncPrintCharMulti( int sc, const char c );
void ncPrintMulti( int sc, const char * string );

#endif