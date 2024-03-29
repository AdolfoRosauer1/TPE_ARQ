#include <stdint.h>

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
#define BEEP 10


uint64_t system_call(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
