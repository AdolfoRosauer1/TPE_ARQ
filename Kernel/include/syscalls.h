#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>
#include <keyboard.h>
#include <time.h>

#define STD_IN 0

#define EXIT 0
#define WRITE 1
#define READ 2
#define CLEAR 3
#define RTC 4
#define POLL_READ 5
#define SYS_BACKSPACE 6

uint64_t pollread(uint64_t fd, char* buf, uint64_t count, uint64_t timeout);

#endif