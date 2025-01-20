#pragma once

#include <iostream>

#define REGISTER_SIZE 2

#define MEMORY_OUT_OF_BOUNDS 1         // 00001
#define COMMAND_NOT_FOUND 2            // 00010
#define DIVISION_BY_ZERO_ERROR 4       // 00100
#define OVERFLOW_DURING_OPERATION 8    // 01000
#define CLOCK_PULSES_IGNORED 16        // 10000

int const memory_size = 100;
int sc_memory[memory_size];
int registr = 0;

int sc_memoryInit() {
    for (int i = 0; i < memory_size; i++) sc_memory[i] = 0;
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address >= memory_size) {
        registr = registr | (1 << (MEMORY_OUT_OF_BOUNDS - 1));
        return -1;
    }
    else {
        sc_memory[address] = value;
        return 0;
    }
}

int sc_memoryGet(int address, int* value) {
    if (address < 0 || address >= memory_size) {
        registr = registr | (1 << (MEMORY_OUT_OF_BOUNDS - 1));
        return -1;
    }
    else {
        *value = sc_memory[address];
        return 0;
    }    
}

int sc_memorySave(char* filename) {    
    FILE* file = fopen (filename, "wb");
    if (file != NULL) {
        fwrite(sc_memory, 1, sizeof(sc_memory), file);
        fclose(file);
        return 0;
    }
    else return -1;
}

int sc_memoryLoad(char* filename) {
    FILE* file = fopen (filename, "rb");
    if (file != NULL) {
        fread(sc_memory, 1, sizeof(sc_memory), file);
        fclose(file);
        return 0;
    }
    else return -1;
}

int sc_regInit(void) {
    registr = 0;
    return 0;
}

int sc_regSet(int registrNum, int value) {
    if (registrNum < 0 || registrNum > REGISTER_SIZE) {
        return -1;
    }
    else {
        if (value == 1)
            registr = registr | (1 << (registrNum - 1));
        else {
            if (value == 0)
                registr = registr & (~(1 << (registrNum - 1)));
            else return -1;
        }         
        return 0;
    }
}

int sc_regGet(int registrNum, int* value) {
    if (registrNum < 0 || registrNum > REGISTER_SIZE) {
        return -1;
    }
    else {
        *value = (registr >> (registrNum - 1)) & 0x1;
        return 0;
    }
}

int sc_commandEncode(int command, int operand, int* value) {
    if (command < 0 || command > 127 || operand < 0 || operand > 127)
        return -1;
    else {
        *value = (command << 7) | operand;
        return 0;
    }
}

int sc_commandDecode(int value, int* command, int* operand) {
    if (value < 0 || value > 16383) {
        registr = registr | (1 << (COMMAND_NOT_FOUND - 1));
        return -1;
    }
    else {
        *command = (value >> 7) & 0x7F;
        *operand = value & 0x7F;
        return 0;
    }
}
