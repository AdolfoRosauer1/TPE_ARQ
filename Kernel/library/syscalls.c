#include <syscalls.h>
#include <time.h>


uint64_t pollread(uint64_t fd, char* buf, uint64_t count, uint64_t timeout)
{
    unsigned int read = (fd == STD_IN)? get_chars(buf,count):get_scancodes((uint8_t*)buf,count);

    if ( timeout != 0 )
    {
        uint64_t start = milis_elapsed(); 
        do
        {
            _hlt();
            read += (fd == STD_IN)? get_chars(buf+read,count-read):get_scancodes((uint8_t*)buf+read,count-read);
        }while ( read == 0 && (milis_elapsed() - start) < timeout );
    }

    return read;
}

void sys_write( uint64_t toWrite, uint64_t writeType,  uint64_t mode, uint64_t screen )
{
    if (writeType==0)
    {
        if ( mode != MULTI_MODE )
            ncPrintChar((char)toWrite);
        else
            ncPrintCharMulti(screen,(char)toWrite);
    }
    else if (writeType==1)
    {
        if ( mode != MULTI_MODE )
            ncPrintDec(toWrite);
        else
            ncPrintDecMulti(screen,toWrite);
    }
    else if (writeType==2)
    {
        if ( mode != MULTI_MODE )
            ncPrintHex(toWrite);
        else
            ncPrintHexMulti(screen,toWrite);
    }
}

void sys_rtc( uint64_t descriptor, uint64_t mode, uint64_t screen )
{
    if ( mode != MULTI_MODE )
    {
        ncPrintDec(getTime(descriptor));
    }else
    {
        ncPrintDecMulti(screen,descriptor);
    }
}

