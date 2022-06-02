// aca va a ir printf putchar etc
#include <system_calls.h>
#include <Utils.h>

void clear()
{
    system_call(CLEAR,0,0,0,0,0);
}

unsigned char getChar()
{
    char c;
    uint64_t i = 0;
    while ( (c = system_call(READ,0,0,0,0,0)) == 0 );
    putChar(c);
    return c;
}

void putChar(char c)
{
    if(c != 0)
        system_call(WRITE,c,0,0,0,0);
}

void print(char * string)
{
    while (*string != 0)
    {
        putChar(*string);
        string++;
    }    
}

int scan(char *buffer, int size)
{
    unsigned char c;
    int length=0;
    while((c = getChar()) != '\n' && length < size)
    {
        if(c == BACKSPACE)
        {
            if(length > 0)
                buffer[length--] = 0;
        } else if(IS_ALPHA(c) || IS_DIGIT(c) || c == ' ')
        {
            putChar(c);
            buffer[length++] = c;  
        }   
    }
    while(buffer[length-1] == ' ')
    {
        while((c = getChar()) != '\n' && length < size)
        {
            if(c == BACKSPACE)
            {
                if(length > 0)
                    buffer[length--] = 0;
            } else if(IS_ALPHA(c) || IS_DIGIT(c) || c == ' ')
            {
                putChar(c);
                buffer[length++] = c;  
            }    
        }
    }
    buffer[length] = 0;
    return length;
}

uint8_t geMinutes()
{
    return system_call(RTC,MINUTES,0,0,0,0);
}