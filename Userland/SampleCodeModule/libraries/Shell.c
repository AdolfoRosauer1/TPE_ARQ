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
        scanf(buffer,MAX_SIZE);
        if ( strcmp(buffer,'exit') == 0 )
            exit=1;
    }
}