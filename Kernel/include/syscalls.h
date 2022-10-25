#ifndef __SYSCALLS_H_
#define __SYSCALLS_H_

#include <stdint.h>
#include <keyboard.h>
#include <time.h>
#include <naiveConsole.h>
#include <video.h>

#define STD_IN 0

#define MULTI_MODE 1

#define EXIT 0
#define WRITE 1
#define READ 2
#define CLEAR 3
#define RTC 4
#define POLL_READ 5
#define REG_INFO 6
#define MULTI_START 7
#define PRINT_MEM 8
#define FONT_SIZE 9

uint64_t pollread(uint64_t fd, char* buf, uint64_t count, uint64_t timeout);
void sys_write(uint64_t toWrite, uint64_t writeType, uint64_t x, uint64_t y, uint64_t color);

#endif