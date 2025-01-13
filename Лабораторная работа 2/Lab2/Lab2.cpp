#include <iostream>

#define REGISTER_SIZE 1

#define MEMORY_OUT_OF_BOUNDS 1         // 001

int const memory_size = 100;
int sc_memory[memory_size];
int registr = 0;
char filename[] = "memory.txt";


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
    FILE* file;
    fopen_s(&file, filename, "w");
    if (file != NULL) {
        fwrite(sc_memory, 1, sizeof(sc_memory), file);
        fclose(file);
        return 0;
    }
    else return -1;
}

int sc_memoryLoad(char* filename) {
    FILE* file;
    fopen_s(&file, filename, "r");
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

int main()
{
    //sc_memoryInit();
    //sc_memorySet(15, 100);
    //int x;
    //int* p = &x;
    //sc_memoryGet(15, p);
    //std::cout << x;    
    //sc_memorySave(filename);
    //sc_memoryLoad(filename);
    //for (int i = 0; i < memory_size; i++) std::cout << sc_memory[i] << std::endl;

    return 0;
}

