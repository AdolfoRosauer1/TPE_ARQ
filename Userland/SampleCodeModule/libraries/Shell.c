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

void printHelp(){
    char *stringout = "En la siguiente lista se muestran los posibles comandos a ser utilizados \n";
    stringout = strcat(stringout, "incluyendo una breve descripcion de que hacen y su uso: \n");
    print(stringout);

    print("help -- muestra una lista de las funciones posibles a ser ejecutadas.\n");
    print("\n");
    print("divbyzero -- muestra el funcionamiento de la excepcion conocida como division por 0.\n");
    print("\n");
    print("codopinv -- muestra el funcionamiento de la excepcion de codigo de oper invalido.\n");
    print("\n");
    print("inforeg -- realiza un dump en pantalla del valor de todos los registros.\n");
    print("\n");
    print("printmem -- realiza un dump en pantalla de los 32bits de memoria desde la direccion recibida como argumento.\n");
    print("\n");    
    print("time -- imprime el dia y la hora del sistema en formato hh:mm-dd/mm/yyyy.\n");
    print("\n");
    print("primos -- imprime los numeros primos desde el 1 en pantalla.\n");
    print("\n");
    print("fibonacchi -- imprime la serie de fibonacchi empezando en el 1...\n");
    print("\n");
    print("com1 | com2 -- el uso del caracter | habilitara la division de la pantalla en 2 y en cada lado se ejecutara cada comando.\n");
    print("\n");
}
