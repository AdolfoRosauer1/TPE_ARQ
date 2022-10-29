#include <video.h>
#include <stdint.h>
#include <fonts.h>
#include <lib.h>
#include <naiveConsole.h>

// codigo basado de https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
struct vbe_mode_info_structure
{
    uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;     // deprecated
    uint8_t window_b;     // deprecated
    uint16_t granularity; // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;        // number of bytes per horizontal line
    uint16_t width;        // width in pixels
    uint16_t height;       // height in pixels
    uint8_t w_char;        // unused...
    uint8_t y_char;        // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direcint_attributes;

    uint32_t framebuffer; // write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

static struct vbe_mode_info_structure *screenData = (void *)0x5C00;

static int currentX = 0;
static int currentY = 0;
unsigned int rows = 0;
static int size = NORMAL;
static char saveScreen[48 * 128] = {0};
static int currentB = 0;
static int reDraw = 0;

void drawPixel(int y, int x, int color)
{
    char *positionInFrameBuffer = (char *)(uint64_t)screenData->framebuffer + 3 * (y * screenData->width + x);

    int blue = color & 0xFF;
    int green = (color >> 8) & 0xFF;
    int red = (color >> 16) & 0xFF;

    *positionInFrameBuffer = blue;
    positionInFrameBuffer++;
    *positionInFrameBuffer = green;
    positionInFrameBuffer++;
    *positionInFrameBuffer = red;
}

void drawChar(char c, int x, int y, int font_color, int background_color)
{
    char *charMap = getCharMap(c);
    // if (!reDraw)
    // {
    //     saveScreen[currentB++] = c;
    // }

    if (x + (2 * CHAR_WIDTH) >= screenData->width)
    { // si llega al final de la linea
        currentY += size * CHAR_HEIGHT / 2;
        rows++;
        newLine();
        currentX += CHAR_WIDTH * 2;
    }
    if (c == '\n')
    { // si es un enter
        currentY += size * CHAR_HEIGHT / 2;
        rows = 0;
        newLine();
        currentX -= CHAR_WIDTH;
        return;
    }
    if (c == '\b' && x >= 3 * CHAR_WIDTH)
    { // si es un back space
        deleteChar();
        return;
    }
    int h = 0;
    for (int i = 0; i < size * CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            unsigned int point = ((charMap[h] >> j) & 0x01);
            if (point == 0)
            {
                drawPixel(y + i, x + CHAR_WIDTH - j, background_color);
            }
            else
            {
                drawPixel(y + i, x + CHAR_WIDTH - j, font_color);
            }
        }
        if (i % size == 0)
        {
            h++;
        }
    }
}

void drawString(char *s, int font_color, int background_color)
{
    for (int i = 0; s[i] != 0; i++)
    {
        drawChar(s[i], currentX, currentY, font_color, background_color);
        if (s[i] != '\b')
            currentX += CHAR_WIDTH;
    }
}

void drawStringWithPos(char *s, int x, int y, int font_color, int background_color)
{
    reDraw = 1;
    for (int i = 0; s[i] != 0; i++)
    {
        drawChar(s[i], x, y, font_color, background_color);
        if (s[i] != '\b')
            x += CHAR_WIDTH;
    }
    reDraw = 0;
}

void newLine()
{
    if (HEIGHT - currentY <= size * CHAR_HEIGHT)
    {
        currentY -= size * CHAR_HEIGHT / 2;
        scrollDown();
    }
    else
    {
        currentY += size * CHAR_HEIGHT / 2;
    }
    currentX = 0;
}

void clearScreen()
{
    reDraw = 1;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            drawPixel(i, j, DEFAULT_BG_COLOR);
        }
    }
    currentX = 0;
    currentY = 0;
    reDraw = 0;
}

void deleteChar()
{
    if (currentX <= 3 * CHAR_WIDTH && rows == 0)
    {
        return;
    }
    if (currentX == 0)
    {
        if (currentY == 0)
        {
            return;
        }
        currentY -= size * CHAR_HEIGHT;
        rows--;
        currentX = WIDTH - (2 * CHAR_WIDTH);
    }
    currentX -= CHAR_WIDTH;
    drawChar(' ', currentX, currentY, DEFAULT_BG_COLOR, DEFAULT_BG_COLOR);
}

void scrollDown()
{
    // codigo basado de basado en: https://forum.osdev.org/viewtopic.php?f=1&t=22702
    unsigned long x = 0;
    unsigned long long *vidmem = (unsigned long long *)screenData->framebuffer;

    while (x <= HEIGHT * WIDTH / 2) // 1024*768/2== HEIGHT * WIDTH /2
    {
        vidmem[x] = vidmem[x + (size * CHAR_HEIGHT * screenData->width / 8) * 3]; /* Valid only for 1024x768x32bpp */
        x = x + 1;
    }    
}

void drawDec(uint64_t value)
{
    drawBase(value, 10);
}

void drawHex(uint64_t value)
{
    drawBase(value, 16);
}

void drawBase(uint64_t value, uint32_t base)
{
    char buffer[1024];
    uintToBase(value, buffer, base);
    drawString(buffer, DEFAULT_FONT_COLOR, DEFAULT_BG_COLOR);
}

void changeFontSize(uint16_t new_size)
{
    clearScreen();
    size = new_size;
    // reDraw = 1;
    // drawString(saveScreen, DEFAULT_FONT_COLOR, DEFAULT_BG_COLOR);
    // reDraw = 0;
}