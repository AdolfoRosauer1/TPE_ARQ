#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void ncScroll()
{
	// uint8_t* i = video;

	// for ( i ; i < LAST_LINE ; i++ )
	// {
	// 	*i = *(i+LINE_LENGTH);
	// }
	// for ( i ; i < LAST_LINE+LINE_LENGTH ; i+=2 )
	// 	*i = ' ';

	int i = 0;

	for ( i ; i < LAST_LINE-video ; i++ )
	{
		video[i] = video[i+LINE_LENGTH];
	}

	for ( i ; i < LAST_LINE+LINE_LENGTH-video ; i+=2 )
	{
		video[i] = ' ';
	}
	currentVideo -= LINE_LENGTH;
	

}

void ncPrintCharColor( const char c, uint8_t color )
{
	if ( currentVideo == LAST_LINE )
		ncScroll();

	if ( c == '\n' )
		ncNewline();
	else{
		*(currentVideo++) = c;
		(*(currentVideo++)) = color;
	}
	
	
}

void ncPrint(const char * string)
{
	int i;

	if ( currentVideo >= LAST_LINE )
		ncScroll();

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(string[i]);
}

void ncPrintChar(char character)
{
	ncPrintCharColor(character,DEFAULT_COLOR);
}

void ncNewline()
{
	do
	{
		ncPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void ncBackSpace()
{
    //Si estoy al principio de la linea (adelante del prompt)
    uint64_t posInLine = (uint64_t)(currentVideo - video) % (uint64_t)(LINE_LENGTH);
    if(posInLine <= PROMPT_SIZE + 1)
        return;

    currentVideo--;
    *currentVideo = DEFAULT_COLOR;
    currentVideo--;
	*currentVideo = ' ';
}


void ncPrintDec(uint64_t value)
{
	ncPrintBase(value, 10);
}

void ncPrintHex(uint64_t value)
{
	ncPrintBase(value, 16);
}

void ncPrintBin(uint64_t value)
{
	ncPrintBase(value, 2);
}

void ncPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    ncPrint(buffer);
}

void ncClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}