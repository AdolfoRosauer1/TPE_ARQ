//syscall handling
#include <stdint.h>
#include <syscalls.h>
#include <naiveConsole.h> //se utiliza las funciones del kernel de forma previsoria para testear


void syscallDispatcher(uint64_t syscall)
{
    switch (syscall)
    {
        case WRITE:
            ncPrint("THIS IS A WRITE");
            break;
        case READ:
            break;
        case EXIT:
            break;
        
            
    }
}