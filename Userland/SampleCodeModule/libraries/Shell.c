#include <Shell.h>

static int exit = 0;

void start_shell()
{
    char buffer[MAX_SIZE] = {0};
    while (!exit)
    {
        scan(buffer,MAX_SIZE);
        putChar('\n');
    }
}