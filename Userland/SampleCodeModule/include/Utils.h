#ifndef _UTILS_H
#define _UTILS_H
#include <system_calls.h>
#include <stdlib.h>

//Para el rtc
#define MINUTES 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

#define BACKSPACE '\b'

#define STD_IN 0

#define MAX_WORDS 5
#define MAX_LENGTH 20

void putChar(char c);
void putDec(int num);
void putHex(int num);
void clear();
unsigned char getChar();
void scanf(char *buffer, int size);
void print(char * string);
uint8_t getTime(int descriptor);

int strlen( char * string );
void strcpy( char * target, char * source, int len );
void divide_string(char target[MAX_WORDS][MAX_LENGTH],char * string );
int strcmp(char string1[], char string2[]);

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define IS_ALPHA(c) (IS_UPPER(c) || IS_LOWER(c))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')


void putCharMulti( int sc, const char c );
void printMulti( int sc, const char * string );
void startMulti();


#endif