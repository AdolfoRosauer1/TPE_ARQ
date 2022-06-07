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

        int i = 0;
        while( command[i][0] != 0 ){
            print(command[i++]);
            putChar('\n');
        }

        command_handler(command);      
    }
}

void getRegInfo()
{
    system_call(REG_INFO,0,0,0,0,0);
}

void exit_shell()
{
    exit = 1;
}

int get_command_code( char command[MAX_LENGTH] )
{
    int index = (INSTRUCTIONS-1)/2;
    int cmp = strcmp(command,commandList[index]);
    int count = 1;
    do
    {
        if ( cmp == 0 )
        {
            return index;
        }
        index += (cmp * index/2);
        (index < 0 )? (index=0):(index=index);
        (index > INSTRUCTIONS )? (index=INSTRUCTIONS):(index=index);
        cmp = strcmp(command,commandList[index]);
        count++;
    } while ( count < INSTRUCTIONS );
    
    return -1;
}

void command_handler( char input[MAX_WORDS][MAX_LENGTH] )
{
    int code1 = get_command_code( input[0] );
    if ( code1 != -1 && code1 != PRINTM )
    {
        if ( input[1] == "|" )
        { //falta una parser function que permita determinar donde estan los args de app1 antes del |, existen casos donde no siempre la app2 esta en input[2]
            int code2 = get_command_code(input[2]);
            if ( code2 != -1 )
            {
                if ( code2 == PRINTM )
                    pipe_handler(code1,code2,EMPTY,input[3]);
                else
                    pipe_handler(code1,code2,EMPTY,EMPTY);
            }else
            {
                print("Invalid use of pipe: Invalid command\n");
            }
        
        }else{ //normal mode
            if ( strlen(input[1]) == 0 )
                command_dispatcher(FULL_SC,code1,EMPTY); 
            else
                print("Invalid argument\n");  
        }
    }else if ( code1 == PRINTM )
    {
        if ( input[2] == "|" )
        {
            int code2 = get_command_code(input[3]);
            if ( code2 != -1 )
            {
                if ( code2 == PRINTM )
                    pipe_handler(code1,code2,input[1],input[4]);
                else
                    pipe_handler(code1,code2,input[1],EMPTY);
            }else
            {
                print("Invalid use of pipe: Invalid command\n");
            }
        }else
        {
            command_dispatcher(FULL_SC,code1,input[1]);
        }
    }
    else
        print("Invalid input \n");
    return;
    
}

void pipe_handler( int app1, int app2, char param1[MAX_LENGTH], char param2[MAX_LENGTH] )
{ // while(1) que distribuye los recursos entre las apps y sus impresiones a pantalla
    int pipeExit = 0;
    startMulti();
    while( !pipeExit )
    {
        printMulti(0,"\n WOW you have entered PIPE MODE!\n");
        printMulti(1,"\n WOW you have entered PIPE MODE!\n");
    }
}

uint64_t command_dispatcher( int mode, int code, char param[MAX_LENGTH] )
{ // 3 modes --> 0 for fullscreen, 1 for left, 2 for right
    if ( mode == FULL_SC || mode == LEFT_SC || mode == RIGHT_SC )
    {
        int sc = mode;
        if ( sc != FULL_SC )
            sc -= 1;
        switch (code)
        {
            case DIV:
                divZero();
                break;
            case EXITP:
                exit_shell();
                break;
            case FIBO:
                return fibo_next();
            case HELP:
                printHelp(sc);
                break;
            case INFOR:
                getRegInfo();
                break;
            case OPCD:
                invalidOpCode();
                break;
            case PRIME:
                return primo_next();
            case PRINTM:
                break; // FALTA COMANDO DE PRINT MEMORY
            case TIME:
                printTime(sc);
                break;
            default:
                print("invalid OPCODE \n");
                break;
        }
    }else
    {
        putDec(mode);
        print(":   Invalid screen mode input\n");
    }
    
    return 0;
}
