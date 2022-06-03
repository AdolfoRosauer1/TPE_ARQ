//syscall handling
#include <stdint.h>
#include <syscalls.h>
#include <keyboard.h>
#include <naiveConsole.h>
#include <time.h>
#include <rtc.h>


uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    switch (rdi) {
        case WRITE:
            ncPrintChar((char)rsi);
            break;
        case READ:
            return pollread(rsi,rdx,rcx,0xFFFF);
            break;
        case POLL_READ:
            return pollread(rsi,rdx,rcx,r8);
            break;
        case CLEAR:
            ncClear();
            break; 
        case RTC:
            getTime(rsi);
            break;   
        case SYS_BACKSPACE:
            ncBackSpace();
            break;    
        default:
            break;
    }
    return 0;
}