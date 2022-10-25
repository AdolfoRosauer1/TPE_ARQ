
#ifndef video_H
#define video_H

#include <stdint.h>


#define WIDTH 1024
#define HEIGHT 768
#define DEFAULT_BG_COLOR 0x000000
#define DEFAULT_FONT_COLOR 0xFFFFFF
#define SMALL 1
#define NORMAL 2
#define LARGE 4

void drawPixel(int x, int y, int color);
void drawChar(char c, int x, int y, int font_color,int background_color);
void drawStringWithPos(char *s, int x, int y, int font_color, int background_color);
void drawString(char * s, int font_color, int background_color);
void clearScreen();
void newLine();
void deleteChar();
void scrollDown();
void drawBase(uint64_t value, uint32_t base);
void drawHex(uint64_t value);
void drawDec(uint64_t value);
void changeFontSize(uint16_t new_size);
#endif