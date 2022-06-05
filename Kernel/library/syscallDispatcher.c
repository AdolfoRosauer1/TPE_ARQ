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
            if (rdx==0)
            {
            ncPrintChar((char)rsi);
            }
            else if (rdx==1)
            {
                ncPrintDec(rsi);
            }
            else if (rdx==2)
            {
                ncPrintHex(rsi);
            }
            break;
        case READ:
            return pollread(rsi,rdx,rcx,0xFFFFFFFF);
        case POLL_READ:
            return pollread(rsi,rdx,rcx,r8);
        case CLEAR:
            ncClear();
            break; 
        case RTC:
            return (getTime(rsi));
        case SYS_BACKSPACE:
            ncBackSpace();
            break;    
        default:
            break;
    }
    return 0;
}