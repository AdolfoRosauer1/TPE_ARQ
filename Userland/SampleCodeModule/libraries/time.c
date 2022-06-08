#include <time.h>
#define MULTI_MODE 1


void printTime( int mode )
{   
    if ( mode == 0 )
    {
        (getTime(mode,0,HOURS));
        (print(":"));
        (getTime(mode,0,MINUTES));
        print("-");
        (getTime(mode,0,DAY));
        print("/");
        (getTime(mode,0,MONTH));
        print("/");
        (getTime(mode,0,YEAR));
        putChar('\n');
        return;
    }else if ( mode == 1 || mode == 2 )
    {
        int sc = mode-1;
        (getTime(MULTI_MODE,sc,HOURS));
        printMulti(sc,":");
        (getTime(MULTI_MODE,sc,MINUTES));
        printMulti(sc,"-");
        (getTime(MULTI_MODE,sc,DAY));
        printMulti(sc,"/");
        (getTime(MULTI_MODE,sc,MONTH));
        printMulti(sc,"/");
        (getTime(MULTI_MODE,sc,YEAR));
        printMulti(sc,"\n");
        return;
    }
    print("Invalid screen mode input\n");
    return;
}