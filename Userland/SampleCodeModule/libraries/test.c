#include <test.h>

static int exit = 0;

void start_test()
{
    startMulti();
    char buffer[MAX_SIZE] = {0};
    while (!exit)
    {
        printMulti(0,"Hello ");
        printMulti(1,"Hola");
        uint64_t aux = 0;
        while( aux < 0xFFFFFF )
            aux++;
    }
}
