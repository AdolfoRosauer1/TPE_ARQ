// aca va a ir printf putchar etc
#include <Utils.h>

void clear()
{
    system_call(CLEAR,0,0,0,0,0);
}

unsigned char getChar()
{
    char c;    
    while ( (system_call(READ,STD_IN,&c,1,0,0)) == 0 );
    return c;
}

void putChar(char c)
{
    if(c != 0)
        system_call(WRITE,c,0,0,0,0);
}

void putDec(int num)
{
    int digits = 1;
    for (int i = num/10; i != 0; digits++,i/=10);
    if (digits == 1)
    {
        putChar('0');
    }
    system_call(WRITE,num,1,0,0,0);
}

void putHex(int num)
{
    print("0x");
    if (num<=15)
    {
        putChar('0');
    }
    system_call(WRITE,num,2,0,0,0);
}

void print(char * string)
{
    while (*string != 0)
    {
        putChar(*string);
        string++;
    }    
}

void scanf(char *buffer, int size)
{
    if ( size == 0 )
        return 1;
        
    uint64_t count = 0;

    do
    {
        char c = getChar();

        if ( c == '\n' )
        {
            buffer[count] = 0;
            putChar(c);
            return;
        }else if (c != '\b')
        {
            if ( count < size-1 )
                buffer[count++] = c;
        }
        putChar(c);
    } while (1);
}

uint8_t getTime(int descriptor)
{
    return system_call(RTC,descriptor,0,0,0,0);
}

int strlen( char * string )
{
    int_fast32_t i = 0;
    while ( string[i] != 0 )
    {
        i++;
    }
    return i;
}

int strcmp(char string1[], char string2[])
{
    int i = 0;
    while(string1[i]!=0 && string2[i]!=0){
        if(string1[i] < string2[i])
            return -1;
        if(string1[i] > string2[i])
            return 1;
        i++;
    }
    if(string1[i]==0 && string2[i]==0)
        return 0;
    if(string1[i]!=0 && string2[i]==0)
        return 1;
    return -1;
}

void strcpy( char * target, char * source, int len )
{
    //strcpy requires for target to have enough allocated memory
    for ( int i = 0 ; source[i] != 0 && i < len ; i++ )
    {
        target[i] = source[i];
    }
}

void divide_string(char target[MAX_WORDS][MAX_LENGTH], char * string )
{
    int start = 0;
    int k = 0;

    for ( int i = 0 ; string[i] != 0 ; i++ )
    {
        if ( string[i] == ' ' )
        {
            int len = i - start;
            if ( len > 0 && len <= MAX_LENGTH && k < MAX_WORDS )
            {
                strcpy(target[k++],string+i,len);
            }else {print("Invalid command arguments"); putChar('\n'); return;}
            start = i+1;
        }
    }

    for ( k ; k < MAX_WORDS ; k++ )
        target[k][0]=0;

    return;

}

// void getCommand(char command[READBUF_LENGTH], char parameters[MAX_PARAMETERS][LENGTH_PARAMETERS], char readbuf[READBUF_LENGTH]) {
//     int i, j, k;

//     for(i=0, j=0; i<READBUF_LENGTH && readbuf[i]!=' '; i++){
//             command[j++] = readbuf[i];
//     }

//     command[j] = 0;

//     while(i<READBUF_LENGTH && readbuf[i]==' '){
//         i++;
//     }

//     for(j=0, k=0; i<READBUF_LENGTH;) {
//         if(k>=MAX_PARAMETERS || j>=LENGTH_PARAMETERS)
//             return;
//         if(readbuf[i]!=' ') {
//             parameters[k][j++] = readbuf[i++];
//         }
//         else {
//             parameters[k][j] = 0;
//             k++;
//             j=0;
//             while(i<READBUF_LENGTH && readbuf[i]==' '){
//                 i++;
//             }
//         }
//     }
// }


void putCharMulti( int sc, const char c )
{
    if ( c != 0 )
        system_call(WRITE,c,0,MULTI_MODE,sc,0);
}

void printMulti( int sc, const char * string )
{
    int i = 0;
    while ( string[i] != 0 )
    {
        putCharMulti( sc, string[i++] );
    }
}

void startMulti()
{
    system_call(MULTI_START,0,0,0,0,0);
}

