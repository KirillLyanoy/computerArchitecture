#include "simple_computer.h"
#include <iostream>

int main() {
    sc_memoryInit();
    sc_memorySet(15, 12);
    

    char filename[] = "memory.txt";
    sc_memorySave(filename);
    sc_memoryLoad(filename);

    int x;
    sc_memoryGet(15, &x);

    std::cout << x << std::endl;

    sc_regInit();

    int value = 1;

    sc_regSet(2, value);
    sc_regGet(2, &value);

    std::cout << "flag: " << value << std::endl;

    int command_encode, command = 5, operand = 10;

    sc_commandEncode(5, 10, &command_encode);
    std::cout << "Encoded value: " << command_encode << "\t Command: " << 5 << "\t Operand: " << 10 << std::endl;


    sc_commandDecode(command_encode, &command, &operand);
    std::cout << "Decoded value: " << command_encode << "\t Command: " << command << "\t Operand: " << operand << std::endl;

    return 0;
}