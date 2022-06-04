#include <stdint.h>

#define EXIT 0
#define WRITE 1
#define READ 2
#define CLEAR 3
#define RTC 4
#define POLL_READ 5
#define WRITE_POS 6



uint64_t system_call(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
