#include <mem.h>
#include <syscalls.h>

uint64_t * backup;
int hasRegisters = 0;

void getRegistersInfo( uint64_t mode , uint64_t sc){
    if ( mode != MULTI_MODE )
    {
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
    }else
    {
        if(hasRegisters == 0){
            ncPrintMulti(sc,"Registers arent saved, press the CTRL key\n");
            return;
        }

        char * regs[REGISTERS_COUNT] = {"RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15", "RSP", "RIP"};
        
        char str[8] = {'0'};
        for(int i=0; i<REGISTERS_COUNT; i++){
            ncPrintMulti(sc,regs[i]);
            ncPrintMulti(sc,": ");
            uint32_t dig = uintToBase(backup[i], str, 16);
        for(int i=0; i < 8-dig; i++){
            ncPrintCharMulti(sc,'0');
        }
            ncPrintMulti(sc,str);
            ncPrintCharMulti(sc,'\n');
        }
    }
    
}

void saveReg(uint64_t * regs){
    backup = regs;
    hasRegisters = 1;
}

void printMemory(uint64_t mode, uint64_t sc, uint64_t start){
    if ( mode != MULTI_MODE )
    {
        char buffer[SIZE] = {'0'};

        uint8_t *address = (uint8_t *)start;
        
        for (int i = 0; i < SIZE; i++){
            uint32_t dig = uintToBase(address[i], buffer, 16);
            for(int i=0; i < 2-dig; i++){
            ncPrintChar('0');
        }
            ncPrint(buffer);
            ncPrintChar(' ');
        }
        
        ncPrintChar('\n');
    }else
    {
        char buffer[SIZE] = {'0'};

        uint8_t *address = (uint8_t *)start;
        
        for (int i = 0; i < SIZE; i++){
            uint32_t dig = uintToBase(address[i], buffer, 16);
            for(int i=0; i < 2-dig; i++){
            ncPrintCharMulti(sc,'0');
        }
            ncPrintMulti(sc,buffer);
            ncPrintCharMulti(sc,' ');
        }
        
        ncPrintCharMulti(sc,'\n');
    }
}