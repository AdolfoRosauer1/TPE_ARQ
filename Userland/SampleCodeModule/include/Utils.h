#ifndef _UTILS_H
#define _UTILS_H

#include <system_calls.h>


//Para el rtc
#define MINUTES 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

//Para fonts
#define SMALL 1
#define NORMAL 2
#define LARGE 3

#define BACKSPACE '\b'

#define STD_IN 0
#define KBD_IN 1

#define MAX_WORDS 5
#define MAX_LENGTH 20
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

void putChar(char c);
void putCharPos(char c, int x, int y);
void putDec(uint64_t num);
void putHex(uint64_t num);
void clear();
unsigned char getChar();
void scanf(char *buffer, int size);
void print(char * string);
void printPos(char * string, int x, int y);
uint8_t getTime(int mode, int scr, int descriptor);

int strlen( char * string );
void strcpy( char * target, char * source, int len );
unsigned long hexaStringToInt(char *s);
void divide_string(char target[MAX_WORDS][MAX_LENGTH],char * string );
int strcmp(char string1[], char string2[]);
void changeFontSize(char * new_size);
void clearScreen();
void drawPixel(int x, int y, int color);

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define IS_ALPHA(c) (IS_UPPER(c) || IS_LOWER(c))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')


void putCharMulti( int sc, const char c );
void printMulti( int sc, const char * string );
void startMulti();
void putDecMulti( int sc, uint64_t value );
void putHexMulti( int sc, uint64_t value );
void beep(int frequency, int time);

#endif