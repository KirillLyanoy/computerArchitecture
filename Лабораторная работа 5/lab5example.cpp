#include "myReadkey.h"
#include <stdio.h>
#include <string>

int main() {
    enum keys key;

    struct termios new_term;
    new_term.c_lflag &= ~ECHO; 
    tcgetattr(0, &new_term);
    tcsetattr(0, TCSANOW, &new_term);  

    printf("enter symbol (echo off): \n");
    char c;
    scanf("%c", &c); 
    printf("entered symbol: %c\n", c);   
  
    rk_mytermrestore();

    printf("echo on.\n");

    return 0;
}