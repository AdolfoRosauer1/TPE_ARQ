#include <exception.h>


static uint64_t ip;
static uint64_t sp;

void exceptionDispatcher(int exception, uint64_t* registers) 
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
	wait(2000);
	reset(registers);
}

void savePointers(uint64_t IP, uint64_t SP)
{
 	ip = IP;
 	sp = SP;
}

void reset(uint64_t *registers)
{
 	registers[IP_INDEX] = ip;
 	registers[SP_INDEX] = sp;
 }

void zeroDivision() 
{
	ncPrint("ERROR DIVIDE BY 0 EXCEPTION\n");
}

void invalidOpcode() 
{
	ncPrint("ERROR INVALID OPCODE EXCEPTION\n");
}