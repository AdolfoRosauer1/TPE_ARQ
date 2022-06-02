#include <keyboard.h>

static unsigned char buffer[MAX_SIZE];
static unsigned int buffer_size = 0;

//https://www.qbasic.net/en/reference/general/scan-codes.htm
static char kbd_US[58][2] = {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, 
    {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, 
    {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, 
    {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, 
    {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, 
    {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, 
    {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, 
    {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
    {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'},
    {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, 
    {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}};

uint8_t getAction(uint8_t scancode) 
{
    if(scancode >= 0x01 && scancode <= 0x3A) 
    {
        return PRESS;
    }
    else if (scancode >= 0x81 && scancode <= 0xBA) 
    {
        return RELEASE;
    }
    return ERROR;
}

int keyboardHandler()
{
    uint8_t scancode = 0;
    uint8_t action;
    while( keyboardStatus )
    {
        scancode = keyPress();
        action = getAction(scancode);
        if (action == PRESS)
        {
            if ( scancode == BACKSPACE )
                ncBackSpace();
            if ( kbd_US[scancode][0] != 0  && buffer_size < MAX_SIZE )
            {
                buffer[buffer_size++] = kbd_US[scancode][0];
                return 1;
            }
        }
        else if (action == RELEASE)
        {
            /* code */
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