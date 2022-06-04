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
            ncPrintChar(rsi,(char)rdx);
            break;
        case READ:
            return pollread(rsi,rdx,rcx,0xFFFF);
            break;
        case POLL_READ:
            return pollread(rsi,rdx,rcx,r8);
            break;
        case CLEAR:
            ncClear(rsi);
            break; 
        case RTC:
            getTime(rsi);
            break;
        case WRITE_POS:
            ncPrintCharPos((char)rsi,(uint8_t)rdx);
            break;
        default:
            break;
    }
    return 0;
}