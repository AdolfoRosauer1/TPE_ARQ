#ifndef NAIVE_CONSOLE_H
#define NAIVE_CONSOLE_H

#include <stdint.h>

#define PROMPT_SIZE 5
#define DEFAULT_COLOR 0x0F
#define LINE_LENGTH width*2
#define LAST_LINE video + (width*height*2) - LINE_LENGTH


typedef struct screen
{
    uint32_t width;
    uint32_t height;
    uint8_t * start;
    uint8_t * current;
    uint32_t offset;
}screen;

void ncStart();
void ncPrint(int sc, const char * string);
void ncPrintChar(int sc,char character);
void ncPrintCharColor( int sc, const char c, uint8_t color );
void ncPrintCharPos(char c, uint8_t pos);
void ncBackSpace(int sc);
void ncNewline(int sc);
void ncPrintDec(uint64_t value);
void ncPrintHex(uint64_t value);
void ncPrintBin(uint64_t value);
void ncPrintBase(uint64_t value, uint32_t base);
void ncClear( int sc );
void ncScroll(int sc);

#endif