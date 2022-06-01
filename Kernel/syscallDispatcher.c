//syscall handling
#include <stdint.h>
#include <syscalls.h>
#include <keyboard.h>
#include <naiveConsole.h> //se utiliza las funciones del kernel de forma previsoria para testear
#include <time.h>


uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    switch (rdi) {
        case WRITE:
            ncPrintChar(get_char());
            break;

        case READ:
            return get_char();
            break;
            

        case CLEAR:
            ncClear();
            break;    
        default:
            break;
    }
    return 0;
}