#include <keyboard.h>
#include <interrupts.h>
#include <video.h>

static uint8_t buffer[MAX_SIZE] = {0};
static unsigned int buffer_size = 0;

static unsigned int mayus = 0;
static unsigned int shift = 0;

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

void keyboardHandler()
{
    uint8_t scancode = 0;
    uint8_t action;

// se fija CTRL PRESS
// lo guarda
// no guarda CTRL RELEASE
    while (keyboardStatus())
    {
        scancode = keyPress();
        action = getAction(scancode);
        if(action == PRESS){
            if ( scancode == CTRL_PRESS )
            {
                saveRegisterInfo();
            }
            else if (scancode == MAYUS)
            {
                mayus=!mayus;
            }
            else if (scancode == SHIFT_PRESS)
            {
                shift=1;
            }
            
            if ( buffer_size < MAX_SIZE)
            {
                buffer[buffer_size++] = scancode;
                return;
            }
        }
        else if (action == RELEASE)
        {
            if (scancode == SHIFT_RELEASE)
            {
                shift = 0;
            }
            
        }
        
    }
    return;
}

void buffer_remove(int length)
{
    int count=0;
    if ( buffer_size > 0 )
    {
      for ( int i = 1 ; i < buffer_size && i < length ; i++ )
      {
        buffer[i-1] = buffer[i];
        count++;
      }
    }
    buffer_size-=count;
    return;
}


char scancode_Ascii( uint8_t scancode )
{
    int state;
    if ( IS_ALPHA(kbd_US[scancode][0]) )
        state = (mayus||shift)? 1:0;
    else
        state = shift;
    
    return (scancode < 58)? (kbd_US[scancode][state]):0;
}


unsigned int get_chars(uint8_t* buf, unsigned int buf_size, unsigned int count)
{
    _cli();

    unsigned int read = 0;
    unsigned int index = 0;

    if ( buf_size < count )
        count = buf_size;

    for ( index ; index < buffer_size && read < count ; index++ )
    {
        uint8_t scancode = buffer[index];
        char c = scancode_Ascii(scancode);
        if ( c != 0  )
        {
            buf[read++] = c;
        }
    }

    buffer_size -= index;
    memcpy(buffer,buffer+index,buffer_size);

    _sti();
    return read;
}

unsigned int get_scancodes(uint8_t* buf, unsigned int count)
{
    _cli();
    if (buffer_size < count)
    {
        count = buffer_size;
    }
    memcpy(buf,buffer,count);
    buffer_size -= count;
    memcpy(buffer,buffer + count, buffer_size);
    _sti();
    return count;
}