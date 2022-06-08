#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>
#include <naiveConsole.h>
#include <interrupts.h>


void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void wait(uint64_t timeout);
#endif
