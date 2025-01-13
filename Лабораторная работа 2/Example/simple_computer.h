#pragma once

#include <iostream>

#define REGISTER_SIZE 2

#define MEMORY_OUT_OF_BOUNDS 1         // 001
#define COMMAND_NOT_FOUND 2            // 010

int sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int* value);

int sc_memorySave(char* filename);

int sc_memoryLoad(char* filename);

int sc_regInit(void);

int sc_regSet(int registrNum, int value);

int sc_regGet(int registrNum, int* value);

int sc_commandEncode(int command, int operand, int* value);

int sc_commandDecode(int value, int* command, int* operand);
