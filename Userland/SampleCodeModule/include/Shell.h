#ifndef _SHELL_H
#define _SHELL_H

#include <Utils.h>
#include <time.h>
#include <help.h>
#include <Fibonacci.h>
#include <Primos.h>
#include <Tron.h>

#define MAX_SIZE 50

#define INSTRUCTIONS 11

static char commandList[INSTRUCTIONS][MAX_LENGTH] = {"divzero", "exit", "fibonacci", "font", "help", "inforeg", "opcode", "primos", "printmem", "time", "tron"};

#define DIV 0
#define EXITP 1
#define FIBO 2
#define CHANGE_FONT 3
#define HELP 4
#define INFOR 5
#define OPCD 6
#define PRIME 7
#define PRINTM 8
#define TIME 9
#define TRON 10

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
void print_mem(int mode, int scr, char *param);
void printHelp(int mode);

void command_handler(char input[MAX_WORDS][MAX_LENGTH]);
void pipe_handler(int app1, int app2, char param1[MAX_LENGTH], char param2[MAX_LENGTH]);
uint64_t command_dispatcher(int mode, int code, char param[MAX_LENGTH]);

#endif