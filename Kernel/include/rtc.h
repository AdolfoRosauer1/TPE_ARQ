#ifndef __RTC_H_
#define __RTC_H_

#include <stdint.h>
#include <time.h>

#define MINUTES 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

extern uint8_t getRTC(uint64_t descriptor);

uint8_t getTime(uint64_t descriptor);

#endif