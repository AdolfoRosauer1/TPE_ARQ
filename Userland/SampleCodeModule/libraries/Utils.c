// aca va a ir printf putchar etc
#include <Utils.h>

void clear()
{
    system_call(CLEAR,0,0,0,0,0);
}

unsigned char getChar()
{
    char c;    
    while ( (system_call(READ,STD_IN,&c,1,0,0)) == 0 );
    return c;
}

void putChar(char c)
{
    if(c != 0)
        system_call(WRITE,c,0,0,0,0);
}

void putDec(int num)
{
    int digits = 1;
    for (int i = num/10; i != 0; digits++,i/=10);
    if (digits == 1)
    {
        putChar('0');
    }
    system_call(WRITE,num,1,0,0,0);
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
            buffer[count] = 0;
            putChar(c);
            return;
        }else if (c != '\b')
        {
            if ( count < size-1 )
                buffer[count++] = c;
        }
        putChar(c);
    } while (1);
}

uint8_t getTime(int descriptor)
{
    return system_call(RTC,descriptor,0,0,0,0);
}

int strlen( char * string )
{
    int_fast32_t i = 0;
    while ( string[i] != 0 )
    {
        i++;
    }
    return i;
}

int strcmp(char string1[], char string2[])
{
    int i = 0;
    while(string1[i]!=0 && string2[i]!=0){
        if(string1[i] < string2[i])
            return -1;
        if(string1[i] > string2[i])
            return 1;
        i++;
    }
    if(string1[i]==0 && string2[i]==0)
        return 0;
    if(string1[i]!=0 && string2[i]==0)
        return 1;
    return -1;
}

