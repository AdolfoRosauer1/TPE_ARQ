#include <naiveConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25;

static screen screens[3];


uint32_t line_length( int sc )
{
	return screens[sc].width*2 + screens[sc].offset;
}

uint32_t last_line( int sc )
{
	return video + (width*height*2) - LINE_LENGTH + screens[sc].offset;
}

void advance_screen( screen sc )
{

}

void ncStart()
{ //to be called in kernel

	// screens[0] to be full screen
	// screens[1] left ||| screens[2] right

	screens[0].width = 80;
	screens[0].height = height;
	screens[0].start = video;
	screens[0].current = screens[0].start;
	screens[0].offset = 0;

	screens[1].width = 39;
	screens[1].height = height;
	screens[1].start = video;
	screens[1].current = screens[1].start;
	screens[1].offset = 0;


	screens[2].width = 39; //39 por la divide line
	screens[2].height = height;
	screens[2].start = video;
	screens[2].current = screens[2].start;
	screens[2].offset = screens[2].width * 2 + 4; //+4 por la divide line

}


void ncScroll(int sc)
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

void ncPrintCharColor( int sc, const char c, uint8_t color )
{
	if ( screens[sc].current == last_line(sc) )
		ncScroll(sc);

	if ( c == '\n' )
		ncNewline(sc);
	else if ( c == '\b' )
		ncBackSpace(sc);
	else{
		*(screens[sc].current++) = c;
		*(screens[sc].current++) = color;
	}
	
	
}


void ncPrintCharPos(char c, uint8_t pos)
{
	video[pos*2] = c;
	video[(pos*2)+1] = DEFAULT_COLOR;
}

void ncPrint(int sc, const char * string)
{
	int i;

	if ( screens[sc].current >= last_line(sc) )
		ncScroll(sc);

	for (i = 0; string[i] != 0; i++)
		ncPrintChar(sc,string[i]);
}

void ncPrintChar(int sc,char character)
{
	ncPrintCharColor(sc,character,DEFAULT_COLOR);
}

void ncNewline(int sc)
{
	do
	{
		ncPrintChar(sc,' ');
	}
	while((uint64_t)(screens[sc].current - video) % (line_length(sc)) != 0); //en duda
}

void ncBackSpace(int sc)
{
    uint64_t posInLine = (uint64_t)(screens[sc].current - video) % (line_length(sc));
    if(posInLine <= PROMPT_SIZE + screens[sc].offset + 1)
        return;

    *(--screens[sc].current) = DEFAULT_COLOR;
	*(--screens[sc].current) = ' ';
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
    // uintToBase(value, buffer, base);
    // ncPrint(buffer);
}

void ncClear( int sc )
{
	int i;

	for (i = 0; i < height * width ; i++)
		{
			video[(i * 2) + screens[sc].offset ] = ' ';
			if ( i % (line_length(sc)) == 0 ) //i es un index pre la siguiente pantalla --> i+=line_length(sc)
				i+= line_length(sc);
		}
	screens[sc].current = screens[sc].start;
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


// ---- SPLIT SCREEN FUNCTIONALITY FUNCTIONS ------