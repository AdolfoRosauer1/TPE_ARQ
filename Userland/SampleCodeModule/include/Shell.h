#ifndef _SHELL_H
#define _SHELL_H

#include <Utils.h>
#include <time.h>
#include <help.h>
#include <Fibonacci.h>
#include <Primos.h>

#define MAX_SIZE 50

#define INSTRUCTIONS 9

static char commandList[INSTRUCTIONS][MAX_LENGTH] = {
    "divzero","exit","fibonacci","help","inforeg","opcode","primos","printmem","time"
    };
#define DIV 0
#define EXITP 1
#define FIBO 2
#define HELP 3
#define INFOR 4
#define OPCD 5
#define PRIME 6
#define PRINTM 7
#define TIME 8

#define FULL_MD 0
#define LEFT_MD 1
#define RIGHT_MD 2

#define LEFT_SC 0
#define RIGHT_SC 1



static const char EMPTY[MAX_LENGTH] = "";

extern void InvOpCodeExc();

void start_shell();
void printTime();
void getRegInfo();
void print_mem(int mode, int scr, char * param);
void printHelp( int mode );

void command_handler( char input[MAX_WORDS][MAX_LENGTH] );
void pipe_handler( int app1, int app2, char param1[MAX_LENGTH], char param2[MAX_LENGTH] );
uint64_t command_dispatcher( int mode, int code, char param[MAX_LENGTH] );

#endif