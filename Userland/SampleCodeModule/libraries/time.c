#include <time.h>


void printTime( int mode )
{   
    if ( mode == 0 )
    {
        putDec(getTime(HOURS));
        print(":");
        putDec(getTime(MINUTES));
        print("-");
        putDec(getTime(DAY));
        print("/");
        putDec(getTime(MONTH));
        print("/");
        putDec(getTime(YEAR));
        putChar('\n');
    return;
    }else if ( mode == 1 || mode == 2 )
    {
        int sc = mode-1;
        putDecMulti(sc,getTime(HOURS));
        printMulti(sc,":");
        putDecMulti(sc,getTime(MINUTES));
        printMulti(sc,"-");
        putDecMulti(sc,getTime(DAY));
        printMulti(sc,"/");
        putDecMulti(sc,getTime(MONTH));
        printMulti(sc,"/");
        putDecMulti(sc,getTime(YEAR));
        printMulti(sc,'\n');
    }
    print("Invalid screen mode input\n");
    return;
}