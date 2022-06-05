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

// void printHelp(){
//     char *stringout = "In the following list are listed all the comands that you can use \n";
//     stringout = strcat(stringout, "including a short description of each and what they do. \n");
//     print(stringout);

//     print("help -- show the list of comands being able to be executed.\n");
//     print("\n");
//     print("divbyzero -- show the functionality of the exception known as divide by 0.\n");
//     print("\n");
//     print("codopinv -- shows the functionality of the exception known as op code invalid.\n");
//     print("\n");
//     print("inforeg -- makes a dump of all the registries in the screen.\n");
//     print("\n");
//     print("printmem -- makes a dunp on screen of a 32 bytes section of memory starting by the address passed as argument.\n");
//     print("\n");    
//     print("time -- prints the day and hour in the format: hh:mm-dd/mm/yyyy.\n");
//     print("\n");
//     print("primos -- prints prime numbers till stoped from the number 1.\n");
//     print("\n");
//     print("fibonacchi -- prints the fibonacchi series starting with 1...\n");
//     print("\n");
//     print("com1 | com2 -- the use of this | caracter divides the screen by half and executes each comand on a part of the screen.\n");
//     print("\n");
// }
