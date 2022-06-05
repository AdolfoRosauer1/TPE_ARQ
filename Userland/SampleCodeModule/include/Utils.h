#ifndef _UTILS_H
#define _UTILS_H
#include <system_calls.h>

//Para el rtc
#define MINUTES 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

#define BACKSPACE '\b'

#define STD_IN 0

void putChar(char c);
void putDec(int num);
void putHex(int num);
void clear();
unsigned char getChar();
void scan(char *buffer, int size);
void print(char * string);
uint8_t getTime(int descriptor);

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define IS_ALPHA(c) (IS_UPPER(c) || IS_LOWER(c))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')


void putCharMulti( int sc, const char c );
void printMulti( int sc, const char * string );
void startMulti();


#endif