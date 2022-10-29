// aca va a ir printf putchar etc
#include <Utils.h>

void clear()
{
    system_call(CLEAR, 0, 0, 0, 0, 0);
}

unsigned char getChar()
{
    char c;
    while ((system_call(READ, STD_IN, &c, 1, 0, 0)) == 0)
        ;
    return c;
}

void putChar(char c)
{
    if (c != 0)
        system_call(WRITE, &c, 0, 0, 0, 0);
}

void putCharPos(char c, int x, int y)
{
    if (c != 0)
        system_call(WRITE, &c, 3, x, y, 0);
}

void putDec(uint64_t num)
{
    system_call(WRITE, num, 1, 0, 0, 0);
}

void putHex(uint64_t num)
{
    print("0x");
    if (num <= 15)
    {
        putChar('0');
    }
    system_call(WRITE, num, 2, 0, 0, 0);
}

void print(char *string)
{
    while (*string != 0)
    {
        putChar(*string);
        string++;
    }
}

void printPos(char *string, int x, int y)
{
    while (*string != 0)
    {
        putCharPos(*string, x, y);
        string++;
        x += CHAR_WIDTH;
    }
}

void scanf(char *buffer, int size) // missing backspace fix
{
    if (size == 0)
        return;

    uint64_t count = 0;

    do
    {
        char c = getChar();

        if (c == '\n')
        {
            buffer[count] = 0;
            putChar(c);
            return;
        }
        else if (c == '\b')
        {
            count--;
        }
        else
        {
            if (count < size - 1)
                buffer[count++] = c;
        }
        putChar(c);

    } while (1);
}

uint8_t getTime(int mode, int scr, int descriptor)
{
    return system_call(RTC, descriptor, mode, scr, 0, 0);
}

int strlen(char *string)
{
    int_fast32_t i = 0;
    while (string[i] != 0)
    {
        i++;
    }
    return i;
}

int strcmp(char string1[], char string2[])
{
    int i = 0;
    while (string1[i] != 0 && string2[i] != 0)
    {
        if (string1[i] < string2[i])
            return -1;
        if (string1[i] > string2[i])
            return 1;
        i++;
    }
    if (string1[i] == 0 && string2[i] == 0)
        return 0;
    if (string1[i] != 0 && string2[i] == 0)
        return 1;
    return -1;
}

void strcpy(char *target, char *source, int len)
{
    // strcpy requires for target to have enough allocated memory
    for (int i = 0; source[i] != 0 && i < len; i++)
    {
        target[i] = source[i];
    }
}

static int pow(int base, unsigned int exp)
{
    int toRet = 1;
    for (int i = 0; i < exp; i++)
        toRet *= base;
    return toRet;
}

unsigned long hexaStringToInt(char *s)
{
    int c;
    unsigned long rta = 0;

    if (s[0] == '0' && s[1] == 'x')
        s += 2;

    int len = strlen(s);

    for (int i = 0; i < len; i++)
    {

        c = s[len - 1 - i] - '0';

        if (c < 0 || c > 9)
        {
            c = s[len - 1 - i] - 'A' + 10;
            if (c < 10 || c > 15)
                return 0;
        }

        rta += c * pow(16, i);
    }
    return rta;
}

void divide_string(char target[MAX_WORDS][MAX_LENGTH], char *string)
{
    int aux = 0;
    int k = 0;
    char *auxPtr = string;

    for (int i = 0; string[i] != 0; i++)
    {
        if (string[i] != ' ')
            target[k][aux++] = string[i];
        else
        {
            target[k++][aux] = 0;
            aux = 0;
        }
    }
    target[k++][aux] = 0;
    for (k; k < MAX_WORDS; k++)
        target[k][0] = 0;

    return;
}

void clearScreen()
{
    system_call(WRITE, 0, 5, 0, 0, 0);
}

void drawPixel(int x, int y, int color)
{
    system_call(WRITE, 0, 4, x, y, color);
}

void putCharMulti(int sc, const char c)
{
    if (c != 0)
        system_call(WRITE, c, 0, MULTI_MODE, sc, 0);
}

void printMulti(int sc, const char *string)
{
    int i = 0;
    while (string[i] != 0)
    {
        putCharMulti(sc, string[i++]);
    }
}

void startMulti()
{
    system_call(MULTI_START, 0, 0, 0, 0, 0);
}

void putDecMulti(int sc, uint64_t value)
{
    system_call(WRITE, value, 1, MULTI_MODE, sc, 0);
}

void putHexMulti(int sc, uint64_t value)
{
    system_call(WRITE, value, 1, MULTI_MODE, sc, 0);
}

void changeFontSize(char *new_size)
{
    if (strcmp(new_size, "small") == 0)
    {
        system_call(FONT_SIZE, SMALL, 0, 0, 0, 0);
    }
    else if (strcmp(new_size, "normal") == 0)
    {
        system_call(FONT_SIZE, NORMAL, 0, 0, 0, 0);
    }
    else if (strcmp(new_size, "large") == 0)
    {
        system_call(FONT_SIZE, LARGE, 0, 0, 0, 0);
    }
    else
        print("Error: addmited size are small, normal, large\n");
}

void beep(int frequency, int time)
{
    system_call(BEEP, frequency, time, 0, 0, 0);
}