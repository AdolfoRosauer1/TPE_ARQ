#include <syscalls.h>
#define GMT -3
#define HOUR 4

uint64_t pollread(uint64_t fd, char *buf, uint64_t count, uint64_t timeout)
{
    unsigned int read = (fd == STD_IN) ? get_chars(buf, count) : get_scancodes((uint8_t *)buf, count);

    if (timeout != 0)
    {
        uint64_t start = milis_elapsed();
        do
        {
            _hlt();
            read += (fd == STD_IN) ? get_chars(buf + read, count - read) : get_scancodes((uint8_t *)buf + read, count - read);
        } while (read == 0 && (milis_elapsed() - start) < timeout);
    }

    return read;
}

void sys_write(uint64_t toWrite, uint64_t writeType, uint64_t x, uint64_t y, uint64_t color)
{
    if (writeType == 0)
    {
        drawString((char *)toWrite, DEFAULT_FONT_COLOR, DEFAULT_BG_COLOR);
    }
    else if (writeType == 1)
    {
        drawDec(toWrite);
    }
    else if (writeType == 2)
    {
        drawHex(toWrite);
    }
    else if (writeType == 3)
    {
        drawStringWithPos((char *)toWrite, x, y, DEFAULT_FONT_COLOR, DEFAULT_BG_COLOR);
    }
    else if (writeType == 4)
    {
        drawPixel(x, y, color);
    }
    else if (writeType == 5)
    {
        clearScreen();
    }
}

void sys_rtc(uint64_t descriptor, uint64_t mode, uint64_t screen)
{
    if (mode != MULTI_MODE)
    {
        if (descriptor != HOUR)
            drawDec(getTime(descriptor));
        else
        {
            int rt = getTime(descriptor);
            ((rt + GMT) < 0) ? (rt = 23 + (rt + GMT)) : (rt = (rt + GMT));
            drawDec(rt);
        }
    }
    else
    {
        if (descriptor != HOUR)
            ncPrintDecMulti(screen, getTime(descriptor));
        else
        {
            int rt = getTime(descriptor);
            ((rt + GMT) <= 0) ? (rt = 23 + (rt + GMT)) : (rt = (rt + GMT));
            ncPrintDecMulti(screen, rt);
        }
    }
}
