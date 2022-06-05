#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

// 2 screen array for left and right
static screen modes[2];

void ncScroll()
{
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
	else if ( c == '\b' )
		ncBackSpace();
	else{
		*(currentVideo) = c;
		currentVideo++;
		*(currentVideo) = color;
		currentVideo++;
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


//Split-Screen functionality methods//




void ncStartModes()
{
	uint32_t half_width = (width/2)-1;

	modes[0].current = video;
	modes[0].height = height;
	modes[0].width = half_width;
	modes[0].offset = 0;

	modes[1].current = video;
	modes[1].height = height;
	modes[1].width = half_width;
	modes[1].offset = width; //la pantalla de la derecha tiene un offset width (media pantalla)

}

void ncStartMulti()
{
	ncClear();

	ncStartModes();
}

uint32_t line_length( int sc )
{
	return modes[sc].width*2;
}

uint8_t * last_line( int sc )
{
	return LAST_LINE + modes[sc].offset;
}

int is_in_screen( int index )
{
	int aux = index/modes[1].offset;
	
	return !( aux%2 == 0 );
}

void ncScrollMulti( int sc )
{
	int i = 0;

	for ( i ; i < LAST_LINE - video ; i++ )
	{
		if ( is_in_screen(i) == sc )
			video[i] = video[i+LINE_LENGTH];
	}

	for ( i = last_line(sc) - video ; i < last_line(sc) - video + line_length(sc) ; i++ )
	{
		video[i++] = ' ';
		video[i] = DEFAULT_COLOR;
	}

	modes[sc].current -= LINE_LENGTH;

}

void ncNewlineMulti( int sc )
{
	do
	{
		ncPrintCharMulti( sc, ' ' );
	}while ( (uint32_t)( modes[sc].current - video ) % (line_length(sc)) != 0 );

}

void ncBackSpaceMulti( int sc )
{
	uint32_t position = (uint32_t)(modes[sc].current - video) % (line_length(sc));

	if ( position <= PROMPT_SIZE )
		return;
	
	*(--modes[sc].current) = DEFAULT_COLOR;
	*(--modes[sc].current) = ' ';
}

void ncPrintCharMulti( int sc, const char c )
{
	if ( modes[sc].current == last_line(sc) )
		ncScrollMulti(sc);
	
	if ( c == '\n' )
		ncNewlineMulti(sc);
	else if ( c == '\b' )
		ncBackSpaceMulti(sc);
	else
	{
		*(modes[sc].current++) = c;
		*(modes[sc].current++) = DEFAULT_COLOR;
	}
}


void ncPrintMulti( int sc, const char * string )
{
	int i;

	for ( i = 0 ; string[i] != 0 ; i++ )
		ncPrintCharMulti(sc,string[i]);
	
}