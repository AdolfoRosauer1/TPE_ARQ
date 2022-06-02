#include <naiveConsole.h>

#define PRESS 1
#define RELEASE 2
#define ERROR -1

#define BACKSPACE 0x0E
#define MAX_SIZE 30

extern unsigned char keyPress();
extern int keyboardStatus();

int keyboardHandler();
unsigned char get_char();