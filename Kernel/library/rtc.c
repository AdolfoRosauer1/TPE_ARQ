#include <rtc.h>

uint8_t getTime(uint64_t descriptor){
    return RTC(descriptor);
}