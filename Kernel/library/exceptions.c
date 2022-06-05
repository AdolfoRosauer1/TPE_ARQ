#include <exception.h>

extern void reset();

static initialState initS;

void exceptionDispatcher(int exception, uint64_t *registers) 
{
	switch(exception){
		case ZERO_EXCEPTION_ID:
			zeroDivision();
			break;
		case INVALID_OPCODE_EXCEPTION_ID:
			invalidOpcode();
			break;
		default:
			return;
	}
	saveRegisterInfo();
	getRegistersInfo();
	for (int i = 0; i < 0xFFFFFFF; i++)
    {
        /* code */
    }
	reset();
}

void zeroDivision() 
{
	ncPrint("ERROR DIVIDE BY 0 EXCEPTION\n");
}

void invalidOpcode() 
{
	ncPrint("ERROR INVALID OPCODE EXCEPTION\n");
}