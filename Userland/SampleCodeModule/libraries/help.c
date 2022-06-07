#include <help.h>


void printHelp( int mode ){
    if ( mode == 0 )
    {
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
    return;
    }else if ( mode == 1 || mode == 2)
    {
    int sc = mode-1;
    char *stringout = "In the following list are listed all the commands that you can use \nincluding a short description of each and what they do. \n";
    printMulti(sc,stringout);

    printMulti(sc,"help -- shows the list of commands being able to be executed.\n");
    printMulti(sc,"\n");
    printMulti(sc,"divzero -- shows the functionality of the exception known as divide by 0.\n");
    printMulti(sc,"\n");
    printMulti(sc,"opcode -- shows the functionality of the exception known as invalid opcode.\n");
    printMulti(sc,"\n");
    printMulti(sc,"inforeg -- makes a dump of all the registries in the screen.\n");
    printMulti(sc,"\n");
    printMulti(sc,"printmem -- makes a memory dump on screen of a 32 bytes section of memory starting by the address passed as an argument.\n");
    printMulti(sc,"\n");    
    printMulti(sc,"time -- prints the day and hour in the format: hh:mm-dd/mm/yyyy.\n");
    printMulti(sc,"\n");
    printMulti(sc,"primos -- prints prime numbers till stoped from the number 1.\n");
    printMulti(sc,"\n");
    printMulti(sc,"fibonacci -- prints the fibonacci series starting with 1\n");
    printMulti(sc,"\n");
    printMulti(sc,"com1 | com2 -- the use of the | caracter divides the screen in half \n and executes each command on the respective part of the screen.\n");
    printMulti(sc,"\n");
    printMulti(sc,"exit -- exits the program\n");
    return;
    }
    putDec(mode);
    print("   Invalid screen mode input\n");
    return;
}