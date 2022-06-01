/* sampleCodeModule.c */
#include <system_calls.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 


	while (1)
	{
		system_call(WRITE,'-',0,0,0,0);
	}
	

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}