#ifndef __RTC_H_
#define __RTC_H_

#include <stdint.h>
#include <time.h>

extern uint8_t RTC(uint64_t descriptor);

uint8_t getTime(uint64_t descriptor);


#endif