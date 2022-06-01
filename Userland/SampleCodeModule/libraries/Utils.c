// aca va a ir printf putchar etc
#include <system_calls.h>
#include <Utils.h>


unsigned char getChar()
{
    char c;
    while ( c = system_call(READ,0,0,0,0,0) == 0 );
    return c;
}

void putChar(char c)
{
    if(c != 0)
        system_call(WRITE,c,0,0,0,0);
}

int scan(char *buffer, int size)
{
    unsigned char c;
    int length=0;
    while((c = getChar()) != '\n' && length < size){
        if(c == BACKSPACE){
            if(length > 0)
                buffer[length--] = 0;
        } else if(IS_ALPHA(c) || IS_DIGIT(c) || c == ' '){
            putChar(c);
            buffer[length++] = c;  
        }   
    }
    while(buffer[length-1] == ' '){
        while((c = getChar()) != '\n' && length < size){
            if(c == BACKSPACE){
                if(length > 0)
                    buffer[length--] = 0;
            } else if(IS_ALPHA(c) || IS_DIGIT(c) || c == ' '){
                putChar(c);
                buffer[length++] = c;  
            } else if(c == SHIFT){
                sys_saveRegs();
            }     
        }
    }
    buffer[length] = 0;
    return length;
}