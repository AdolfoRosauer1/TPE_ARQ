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

void getRegInfo(int mode)
{
    if ( mode != FULL_MD ){
        int sc = mode-1;
        system_call(REG_INFO,MULTI_MODE,sc,0,0,0);
    }else
        system_call(REG_INFO,mode,0,0,0,0);
}

void print_mem(int mode, int scr, char * param)
{
    unsigned long address = hexaStringToInt(param);
    system_call(PRINT_MEM,mode,scr,address,0,0);
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
        index += cmp;
        (index < 0 )? (index=0):(index=index);
        (index > INSTRUCTIONS )? (index=INSTRUCTIONS):(index=index);
        cmp = strcmp(command,commandList[index]);
        count++;
    } while ( count < INSTRUCTIONS );
    print("Invalid OPCODE");
    return -1;
}

void command_handler( char input[MAX_WORDS][MAX_LENGTH] )
{
    int code1 = get_command_code( input[0] );
    if ( code1 != -1 && code1 != PRINTM )
    {
        if ( strcmp(input[1],"|") == 0 )
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
            {
                if ( code1 != FIBO && code1 != PRIME )
                    command_dispatcher(FULL_MD,code1,EMPTY);
                else
                    full_screen_infinite(code1);
            } 
            else
                print("Invalid argument\n");  
        }
    }else if ( code1 == PRINTM )
    {
        if ( strcmp(input[2],"|") == 0 )
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
            command_dispatcher(FULL_MD,code1,input[1]);
        }
    }
    else
        print("Invalid input \n");
    return;
    
}

void unpipe_my_pipe()
{
    clear();
    return;
}

void pipe_handler( int app1, int app2, char param1[MAX_LENGTH], char param2[MAX_LENGTH] )
{ // while(1) que distribuye los recursos entre las apps y sus impresiones a pantalla
    int pipeExit = 0;
    int app1_dispatched = 0;
    int app2_dispatched = 0;
    startMulti();
    if ( app1 != FIBO && app1 != PRIME ){
        command_dispatcher(LEFT_MD,app1,param1);
        app1_dispatched = 1;
    }
    if ( app2 != FIBO && app2 != PRIME ){
        command_dispatcher(RIGHT_MD,app2,param2);
        app2_dispatched = 1;
    }
    if ( !app1_dispatched || !app2_dispatched ) {
        if ( app1 == FIBO || app2 == FIBO )
            start_fibo();
        if ( app1 == PRIME || app2 == PRIME )
            start_prime();
        uint64_t c = 0;
        while( 1 )
        {
            system_call(POLL_READ,1,&c,1,1000,0); //KBD_IN es 1
            if ( c == 1 )
            {
                unpipe_my_pipe();
                return;
            }
            if ( !app1_dispatched  && !app2_dispatched )
            {
                if ( app1 == app2 )
                {
                    uint64_t toPrint = command_dispatcher(FULL_MD,app1,EMPTY); //SCREEN MODE does not matter for PRIME and FIBO apps
                    putDecMulti(LEFT_SC,toPrint);
                    printMulti(LEFT_SC,"\n");
                    putDecMulti(RIGHT_SC,toPrint);
                    printMulti(RIGHT_SC,"\n");
                }else
                {
                    uint64_t toPrint1 = command_dispatcher(FULL_MD,app1,EMPTY);
                    uint64_t toPrint2 = command_dispatcher(FULL_MD,app2,EMPTY);
                    putDecMulti(LEFT_SC,toPrint1);
                    printMulti(LEFT_SC,"\n");
                    putDecMulti(RIGHT_SC,toPrint2);
                    printMulti(RIGHT_SC,"\n");
                }
            }else if ( !app1_dispatched )
            {
                uint64_t toPrint = command_dispatcher(FULL_MD,app1,EMPTY);
                putDecMulti(LEFT_SC,toPrint);
                printMulti(LEFT_SC,"\n");
            }else
            {
                uint64_t toPrint = command_dispatcher(FULL_MD,app2,EMPTY);
                putDecMulti(RIGHT_SC,toPrint);
                printMulti(RIGHT_SC,"\n");
            }
        }
    }
    unpipe_my_pipe();
}

void full_screen_infinite( int code )
{
    uint64_t c = 0;
    if ( code == PRIME )
        start_prime();
    if ( code == FIBO )
        start_fibo();
    while( 1 )
    {
    uint64_t toPrint = command_dispatcher(0,code,EMPTY);
    putDec(toPrint);
    print("\n");
    system_call(POLL_READ,1,&c,1,100,0); //KBD_IN es 1
        if ( c == 1 )
            break;
    }
    putChar('\n');
}

uint64_t command_dispatcher( int mode, int code, char param[MAX_LENGTH] )
{ // 3 modes --> 0 for fullscreen, 1 for left, 2 for right
    if ( mode == FULL_MD || mode == LEFT_MD || mode == RIGHT_MD )
    {
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
                printHelp(mode);
                break;
            case INFOR:
                getRegInfo(mode);
                break;
            case OPCD:
                invalidOpCode();
                break;
            case PRIME:
                return primo_next();
            case PRINTM:
                print_mem(mode,((mode==FULL_MD)?0:mode-1),param);
                break;
            case TIME:
                printTime(mode);
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
