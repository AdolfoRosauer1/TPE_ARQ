#include <syscalls.h>



uint64_t pollread(uint64_t fd, char* buf, uint64_t count, uint64_t timeout)
{
    unsigned int read = (fd == STD_IN)? get_chars(buf,count):get_scancodes((uint8_t*)buf,count);

    if ( timeout != 0 )
    {
        uint64_t start = milis_elapsed(); 
        do
        {
            _hlt();
            read += (fd == STD_IN)? get_chars(buf+read,count-read):get_scancodes((uint8_t*)buf,count);
        }while ( read == 0 && (milis_elapsed() - start) < timeout );
    }

    return read;
}