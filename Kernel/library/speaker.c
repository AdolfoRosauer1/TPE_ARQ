#include <speaker.h>

// Play sound using built in speaker
// Basado en codeigo de https://wiki.osdev.org/PC_Speaker
void play_sound(uint32_t nFrequence)
{
    uint32_t Div;
    uint8_t tmp;

    // Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(Div));
    outb(0x42, (uint8_t)(Div >> 8));

    // And play the sound using the PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
        outb(0x61, tmp | 3);
    }
}

void set_pit_count(unsigned count) {
	// Disable interrupts
	_cli();
 
	// Set low byte
	outb(0x40,count&0xFF);		// Low byte
	outb(0x40,(count&0xFF00)>>8);	// High byte
	return;
}

// make it shutup
void nosound()
{
    uint8_t tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}

void beep(int nFrequence, int time){
    play_sound(nFrequence);
    wait(time);
    nosound();
}