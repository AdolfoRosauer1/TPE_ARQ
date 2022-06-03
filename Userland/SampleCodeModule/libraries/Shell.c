#include <Shell.h>

static int exit = 0;

void start_shell()
{
    clear();
    print("Welcome to BocaOS");
    putChar('\n');
    char buffer[MAX_SIZE] = {0};
    while (!exit)
    {
        print(">> ");
        scanf(buffer,MAX_SIZE);
        if ( strcmp("exit",buffer) == 0 )
        {
            exit = 1;
        }
        
    }
}