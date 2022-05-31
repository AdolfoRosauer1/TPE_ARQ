// aca va a ir printf putchar etc
#include <system_calls.h>

unsigned char get_input()
{
    return system_call(READ,0,0,0,0,0);
}

unsigned char get_char()
{
    char c;
    while ( c = system_call(READ,0,0,0,0,0) == 0 );
    
    return c;

}