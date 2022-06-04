#include <naiveConsole.h>
#include <lib.h>

#define PRESS 1
#define RELEASE 2
#define ERROR -1

#define BACKSPACE 0x0E
#define CTRL_PRESS 0x1D
#define CTRL_RELEASE 0x9D
#define MAYUS 0x3A
#define SHIFT_PRESS 0x2A
#define SHIFT_RELEASE 0xAA

#define MAX_SIZE 30

extern unsigned char keyPress();
extern int keyboardStatus();
char scancode_Ascii( uint8_t scancode );
void keyboardHandler();
unsigned int get_scancodes(uint8_t* buf, unsigned int count);
unsigned int get_chars();

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define IS_ALPHA(c) (IS_UPPER(c) || IS_LOWER(c))
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')