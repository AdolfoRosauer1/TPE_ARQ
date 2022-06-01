#ifndef _UTILS_H
#define _UTILS_H

#define BACKSPACE 0x0E
#define SHIFT 201


void putChar(char c);
void clear();
unsigned char getChar();

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define IS_ALPHA(c) (IS_UPPER(c) || IS_LOWER(c))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')


#endif