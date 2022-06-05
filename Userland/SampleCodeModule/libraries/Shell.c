#include <Shell.h>

static int exit = 0;

void divZero()
{
    int x = 1/0;
}

void invalidOpCode()
{
    InvOpCodeExc();
}

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
        else if ( strcmp("/help",buffer) == 0 )
        {
            help();
        }
        else if ( strcmp("/time",buffer) == 0 )
        {
            printTime();
        }        
        else if ( strcmp("/divzero",buffer) == 0 )
        {
            divZero();
        }
        else if ( strcmp("/opcode",buffer) == 0 )
        {
            invalidOpCode();
        }       
        else if ( strcmp("/inforeg",buffer) == 0 )
        {
            getRegInfo();
        }
        else
        {
            print("Invalid command, try /help\n");
        }        
    }
}

void getRegInfo()
{
    system_call(REG_INFO,0,0,0,0,0);
}

void help()
{
    print("  /time - Prints the current time\n");
    print("  /divzero - Prints the division by zero exception\n");
    print("  /opcode - Prints the opcode exception\n");
    print("  /inforeg - Prints all of the registers, if they were saved (use CTRL to save their current state)\n");

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
