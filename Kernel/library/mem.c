#include <mem.h>

uint64_t * backup;
int hasRegisters = 0;

void getRegistersInfo(){
    if(hasRegisters == 0){
        ncPrint("Registers arent saved, press the CTRL key\n");
        return;
    }

    char * regs[REGISTERS_COUNT] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15", "RSP", "RIP"};
    
    char str[8] = {'0'};
    for(int i=0; i<REGISTERS_COUNT; i++){
        ncPrint(regs[i]);
        ncPrint(": ");
        uint32_t dig = uintToBase(backup[i], str, 16);
       for(int i=0; i < 8-dig; i++){
           ncPrintChar('0');
       }
        ncPrint(str);
        ncPrintChar('\n');
    }
    
}

void savereg(uint64_t * regInfo){
    backup = regInfo;
    hasRegisters = 1;
}

void printMemory(uint64_t argument){

    char dump[32] = {'0'};

    uint8_t *memAddress = (uint8_t *)argument;
    
    for (int i = 0; i < 32; i++){
        uint32_t dig = uintToBase(memAddress[i], dump, 16);
        for(int i=0; i < 2-dig; i++){
           ncPrintChar('0');
       }
        ncPrint(dump);
        ncPrintChar(' ');
    }
    
    ncPrintChar('\n');
}