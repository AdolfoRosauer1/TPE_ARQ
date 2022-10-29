#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

extern void outb(uint16_t port, uint8_t value);

extern uint8_t inb(uint16_t port);

void play_sound(uint32_t nFrequence);






#endif