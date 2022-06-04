#include <Shell.h>

static int exit = 0;

void start_shell()
{
    clear(0);
    print(0,"Welcome to BocaOS");
    putChar(0,'\n');
    char buffer[MAX_SIZE] = {0};
    while (!exit)
    {
        print(0,">> ");
        scanf(buffer,MAX_SIZE);
        system_call(WRITE_POS,'f',0,0,0,0);
        if ( strcmp("exit",buffer) == 0 )
        {
            exit = 1;
        }

        // uint8_t minutes = getMinutes();

        // system_call(WRITE_POS,minutes+'0',40,0,0,0);
        
    }
}