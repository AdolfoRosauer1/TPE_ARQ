//syscall handling
#include <stdint.h>
#include <syscalls.h>
#include <keyboard.h>
#include <naiveConsole.h>
#include <time.h>
#include <rtc.h>


uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    char c;
    switch (rdi) {
        case WRITE:
            ncPrintChar((char)rsi);
            break;
        case READ:
            c = get_char();
            return c;
            break;
        case CLEAR:
            ncClear();
            break; 
        case RTC:
            getTime(rsi);
            break;    
        default:
            break;
    }
    return 0;
}