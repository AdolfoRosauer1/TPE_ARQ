#include <keyboard.h>

static unsigned char buffer[MAX_SIZE];
static unsigned int buffer_size = 0;

 unsigned char kbd_US [128] ={
    0,  27, /* <-- Escape */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', /* <-- Tab */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    200, /* <-- control key */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    201, /* Shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
    '*',
    202,  /* Alt */
    ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
    };

int keyboardHandler()
{
    unsigned char scancode = 0;
    while( keyboardStatus )
    {
        scancode = keyPress();
        if ( scancode == BACKSPACE )
            ncBackSpace();
        if ( kbd_US[scancode] != 0  && buffer_size < MAX_SIZE )
        {
            buffer[buffer_size++] = kbd_US[scancode];
            return 1;
        }
    }
    return 0;
}

void buffer_remove()
{
    if ( buffer_size > 0 )
    {
      for ( int i = 1 ; i < buffer_size ; i++ )
      {
        buffer[i-1] = buffer[i];
      }
    }
    buffer_size--;
    return;
}

unsigned char get_char()
{

    if ( buffer_size <= 0 )
    {
        return 0;
    }
    unsigned char toReturn = buffer[0];
    buffer_remove();

    return toReturn;
}