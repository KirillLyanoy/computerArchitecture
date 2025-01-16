#include <stdio.h>
#include <fcntl.h>
#include "myBigChars.h"


int main() {
    char char_arr[] = { 'l', 'j', 'k', 'x', 'a', 'm', 'q'};

    printf("Without encoding: %s\n", char_arr);
    printf("With encoding: ");
    bc_printA(char_arr);
    printf("\n");

    bc_box(5, 5, 20, 20); 

    int SYMBOL_0[2] = { BIG_SYMBOL_0 };
    int SYMBOL_9[2] = { BIG_SYMBOL_9 };
    int SYMBOL_5[2] = { BIG_SYMBOL_5 };
    bc_printbigchar(SYMBOL_9, 2, 30, WHITE, GREEN);
    bc_printbigchar(SYMBOL_5, 10, 40, MAGENTA, CYAN); 
    bc_printbigchar(SYMBOL_0, 20, 15, YELLOW, RED); 

    bc_setbigcharpos(SYMBOL_0, 4, 7, 0);
    bc_printbigchar(SYMBOL_0, 30, 15, YELLOW, RED); 

    int value;
    bc_getbigcharpos(SYMBOL_0, 3, 7, &value);
    printf("Value (number - 0; row - 3, column - 7) = %d\n", value);
    bc_getbigcharpos(SYMBOL_9, 1, 7, &value);
    printf("Value (number - 9; row - 1, column - 7) = %d\n", value);

    
    int fd = open("numbers.bin", O_RDWR | O_CREAT, 0644);
    
    bc_bigcharwrite(fd, SYMBOL_0, 1);
    printf("Number written in file.\n");
          
    int read_number[2];
    int read_count;
    bc_bigcharread(fd, read_number, 1, &read_count);

    lseek(fd, 0, SEEK_SET);
    
    printf("Number readed from file.");
    bc_printbigchar(read_number, 60, 70, BLUE, WHITE);
  
    close(fd);
    return 0;
}