#ifndef _SHELL_H
#define _SHELL_H

#include <Utils.h>

#define MAX_SIZE 50

#define INSTRUCTIONS 9

static char commandList[INSTRUCTIONS][MAX_LENGTH] = {
    "divzero","exit","fibonacci","help","inforeg","opcode","primos","printmem","time"
    };

extern void InvOpCodeExc();

void start_shell();
void printTime();
void getRegInfo();
void printHelp();

#endif