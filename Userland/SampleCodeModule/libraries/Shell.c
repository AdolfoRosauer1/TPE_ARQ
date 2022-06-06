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
        char command[MAX_WORDS][MAX_LENGTH];
        divide_string(command,buffer);

        for( int i = 0 ; i < MAX_WORDS ; i++ ){
            print(command[i]);
            putChar('\n');
        }

        if ( strcmp("exit",buffer) == 0 )
        {
            exit = 1;
        }
        else if ( strcmp("help",buffer) == 0 )
        {
            printHelp();
        }
        else if ( strcmp("time",buffer) == 0 )
        {
            printTime();
        }        
        else if ( strcmp("divzero",buffer) == 0 )
        {
            divZero();
        }
        else if ( strcmp("opcode",buffer) == 0 )
        {
            invalidOpCode();
        }       
        else if ( strcmp("inforeg",buffer) == 0 )
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

void printHelp(){
    char *stringout = "In the following list are listed all the commands that you can use \nincluding a short description of each and what they do. \n";
    print(stringout);

    print("help -- shows the list of commands being able to be executed.\n");
    print("\n");
    print("divzero -- shows the functionality of the exception known as divide by 0.\n");
    print("\n");
    print("opcode -- shows the functionality of the exception known as invalid opcode.\n");
    print("\n");
    print("inforeg -- makes a dump of all the registries in the screen.\n");
    print("\n");
    print("printmem -- makes a memory dump on screen of a 32 bytes section of memory starting by the address passed as an argument.\n");
    print("\n");    
    print("time -- prints the day and hour in the format: hh:mm-dd/mm/yyyy.\n");
    print("\n");
    print("primos -- prints prime numbers till stoped from the number 1.\n");
    print("\n");
    print("fibonacci -- prints the fibonacci series starting with 1\n");
    print("\n");
    print("com1 | com2 -- the use of the | caracter divides the screen in half \n and executes each command on the respective part of the screen.\n");
    print("\n");
    print("exit -- exits the program\n");
}


int get_command_code( char command[MAX_LENGTH] )
{
    int index = INSTRUCTIONS/2;
    int cmp = strcmp(command,commandList[index]);
    int count = 1;
    do
    {
        if ( cmp == 0 )
            return index;
        index += (cmp * index/2);
        int cmp = strcmp(command,commandList[index]);
        count++;
    } while ( count < INSTRUCTIONS );
    

    return -1;
}

void command_handler( char input[MAX_WORDS][MAX_LENGTH] )
{
    if ( input[1] == '|' )
    {
       int code1 = get_command_code(input[0]);
       int code2 = get_command_code(input[2]);

       pipe_mode(code1,code2,input);
       
    }else{ //normal mode
        int code = get_command_code(input[0]);
        if ( code != -1 )
            command_dispatcher(code,input+1);
        
    }
    
}

void pipe_mode( int app1, int app2, char input[MAX_WORDS][MAX_LENGTH] )
{
    
}

command_dispatcher( int code, char input[MAX_WORDS-1][MAX_LENGTH] )
{ // 3 modes --> 0 for fullscreen, 1 for left, 2 for right

}
