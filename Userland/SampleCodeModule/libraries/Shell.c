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
        if ( strcmp("/exit",buffer) == 0 )
        {
            exit = 1;
        }
        else if ( strcmp("/time",buffer) == 0 )
        {
            printTime();
        }
        else
        {
            print("Invalid command, try /help\n");
        }        
    }
}

void printTime()
{   
    putDec(getTime(HOURS));
    print(":");
    putDec(getTime(MINUTES));
    print("-");
    putDec(getTime(DAY));
    print("/");
    putDec(getTime(MONTH));
    print("/");
    putDec(getTime(YEAR));
    putChar('\n');
}