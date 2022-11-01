#include <help.h>

void printHelp(int mode)
{
    if (mode == 0)
    {
        char *stringout = "In the following list are all the commands that you can use \nincluding a short description of each and what they do. \n\n";
        print(stringout);

        print("help -- shows the list of commands being able to be executed.\n");
        print("divzero -- shows the functionality of the exception known as divide by 0.\n");
        print("opcode -- shows the functionality of the exception known as invalid opcode.\n");
        print("inforeg -- makes a dump of all the registries in the screen.\n");
        print("printmem -- makes a memory dump on screen of a 32 bytes section of memory starting by the address passed as an argument.\n");
        print("time -- prints the day and hour in the format: hh:mm-dd/mm/yyyy.\n");
        print("primos -- prints prime numbers until stopped. Starting from the number 1.\n");
        print("font -- clears the screen and changes the font size. Admits the arguments: small, normal, large\n");
        print("tron -- Starts the Tron game\n");
        // print("fibonacci -- prints the fibonacci series starting with 1\n");
        // print("com1 | com2 -- the use of the | caracter divides the screen in half \n and executes each command on the respective part of the screen.\n");
        print("exit -- exits the program\n");
        print("Use ESC to exit fibonacci or primos program\n");
        return;
    }
    else if (mode == 1 || mode == 2)
    {
        int sc = mode - 1;
        char *stringout = "In the following list are all the commands\n";
        printMulti(sc, stringout);

        printMulti(sc, "help - shows the list of commands\n");
        printMulti(sc, "divzero - shows the exception known as divide by 0.\n");
        printMulti(sc, "opcode - shows the exception known as invalid opcode.\n");
        printMulti(sc, "inforeg - makes a dump of all registries on screen.\n");
        printMulti(sc, "printmem - makes a memory dump of memory starting by the argument.\n");
        printMulti(sc, "time - prints the day and hour\n");
        printMulti(sc, "primos - prints prime numbers until stoped\n");
        printMulti(sc, "fibonacci - prints the fibonacci series\n");
        printMulti(sc, "com1 | com2 - the | caracter divides the screen in half\n");
        printMulti(sc, "exit - exits the program\n");
        printMulti(sc, "PRESS ESC TO EXIT PIPE MODE");
        return;
    }
    putDec(mode);
    print(":   Invalid screen mode input\n");
    return;
}