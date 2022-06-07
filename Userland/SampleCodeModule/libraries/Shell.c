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
    // int index = (INSTRUCTIONS-1)/2;
    int index = 3;
    print("\n will analyze:  ");
    print(command);
    int cmp = strcmp(command,commandList[index]);
    int count = 1;
    do
    {
        print("\n index:  ");
        putDec(index);
        print("     cmp:  ");
        if ( cmp == 0 || cmp == 1 || cmp == -1 )
        putDec((uint64_t)cmp);
        if ( cmp == 0 )
        {
            print("\n COMMAND CODE FOUND \n");
            return index;
        }
        index += (cmp * index/2);
        (index < 0 )? (index=0):(index=index);
        (index > INSTRUCTIONS )? (index=INSTRUCTIONS):(index=index);
        cmp = strcmp(command,commandList[index]);
        count++;
    } while ( count < INSTRUCTIONS );
    
    print("\n COMMAND CODE NOT FOUND \n");
    return -1;
}

void command_handler( char input[MAX_WORDS][MAX_LENGTH] )
{
    int code1 = get_command_code( input[0] );
    if ( code1 != -1 && code1 != PRINTM )
    {
        if ( input[1] == '|' )
        { //falta una parser function que permita determinar donde estan los args de app1 antes del |, existen casos donde no siempre la app2 esta en input[2]
            int code2 = get_command_code(input[2]);
            if ( code2 != -1 )
                pipe_handler(code1,code2,input);
            else
            {
                print("Invalid use of pipe: Invalid command\n");
            }
        
        }else{ //normal mode
            command_dispatcher(FULL_SC,code1,input+1);   
        }
    }else if ( code1 == PRINTM )
    {
        
    }
    return;
    
}

void pipe_handler( int app1, int app2, char input[MAX_WORDS][MAX_LENGTH] )
{ // while(1) que distribuye los recursos entre las apps y sus impresiones a pantalla
    int pipeExit = 0;
    while( !pipeExit )
    {
        
    }
}

uint64_t command_dispatcher( int mode, int code, char input[MAX_WORDS-1][MAX_LENGTH] )
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
        print("   Invalid screen mode input\n");
    }
    
    return 0;
}
