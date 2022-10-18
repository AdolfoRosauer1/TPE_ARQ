
#ifndef video_H
#define video_H

#define WIDTH 1024
#define HEIGHT 768
#define DEFAULT_BG_COLOR 0x000000
#define DEFAULT_FONT_COLOR 0xFFFFFF

void drawPixel(int x, int y, int color);
void drawChar(char c, int x, int y, int font_color,int background_color);
void drawString(char * s, int font_color, int background_color);
void clearScreen();
void newLine();
void deleteChar();
void scrollDown();
#endif