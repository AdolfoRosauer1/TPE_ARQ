// aca va a ir printf putchar etc
#include <Utils.h>

void clear()
{
    system_call(CLEAR,0,0,0,0,0);
}

unsigned char getChar()
{
    char c;    
    while ( (system_call(POLL_READ,STD_IN,&c,1,200,0)) == 0 );
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

void scanf(char *buffer, int size)
{
    if ( size == 0 )
        return 1;
        
    uint64_t count = 0;

    do
    {
        char c = getChar();

        if ( c == '\n' )
        {
            buffer[count++] = c;
            buffer[count] = 0;
            return;
        }else
        {
            if ( count < size-1 )
                buffer[count++] = c;
        }
        putChar(c);
    } while (1);
}

uint8_t geMinutes()
{
    return system_call(RTC,MINUTES,0,0,0,0);
}