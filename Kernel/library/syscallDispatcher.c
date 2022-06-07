//syscall handling
#include <stdint.h>
#include <syscalls.h>
#include <keyboard.h>
#include <naiveConsole.h>
#include <time.h>
#include <rtc.h>
#include <mem.h>


uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    switch (rdi) {
        case WRITE:
            sys_write(rsi,rdx,rcx,r8);
            break;
        case READ:
            return pollread(rsi,rdx,rcx,0xFFFFFFFF);
        case POLL_READ:
            return pollread(rsi,rdx,rcx,r8);
        case CLEAR:
            ncClear();
            break; 
        case RTC:
            ncPrintDec(getTime(rsi));
            break;
        case REG_INFO:
            getRegistersInfo();
            break;
        case MULTI_START:
            ncStartMulti();
            break;    
        default:
            break;
    }
    return 0;
}