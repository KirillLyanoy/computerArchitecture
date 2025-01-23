#pragma once

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BIG_SYMBOL_0 1111638588, 1010975298
#define BIG_SYMBOL_1 303306768, 2081427472
#define BIG_SYMBOL_2 541213244, 2114193424
#define BIG_SYMBOL_3 943866428, 1010975296
#define BIG_SYMBOL_4 606613536, 538976382
#define BIG_SYMBOL_5 1040319102, 472006720
#define BIG_SYMBOL_6 1040335420, 1010975298
#define BIG_SYMBOL_7 270549118, 134744072
#define BIG_SYMBOL_8 1010975292, 1010975298
#define BIG_SYMBOL_9 1111638588, 1010974844
#define BIG_SYMBOL_PLUS 404226048, 1579134

enum color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    DEFAULT = 9
};

int bc_printA (char * str) {
    if (str == NULL) return -1;
    
    printf("\033(0%s\033(B", str);   
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) return -1;
    
    printf("\033[%d;%dH\033(0l", x1, y1);

    for (int i = 1; i < y2; i++) {
        printf("q");
    }
    printf("k\n\033[%d;%dH", x1 + 1, y1);

    for (int i = 1; i < x2; i++) {
        printf("x");
        for (int j = 1; j < y2; j++) {
            printf(" ");
        }
        printf("x\n\033[%d;%dH", x1 + i, y1); 
    }

    printf("m");

    for (int i = 1; i < y2; i++) {
        printf("q");
    }
    printf("j\n\033(B");

    return 0;
}

int bc_printbigchar (int symbol[2], int x, int y, enum color fg_color, enum color bg_color) {
    if (fg_color < BLACK || fg_color > DEFAULT || bg_color < BLACK || fg_color > DEFAULT || x < 0 || y < 0) return -1;
    printf("\033[%d;%dH\033(0", x, y);

    for (int numbers = 0; numbers < 2; numbers++) {
        int temp_number = symbol[numbers];
        for (int i = 0; i < 4; i++) {
            int temp = temp_number & 0xff;
            for (int j = 0; j < 8; j++) {
                int rm_temp = temp & 1;
                if (rm_temp == 0) printf("\033[4%dm \033[49m", bg_color);
                else printf("\033[3%dm\033[4%dma\033[39m\033[49m", fg_color, bg_color);
                temp = temp >> 1;
            }
            printf("\n\033[%d;%dH", ++x, y);
            temp_number = temp_number >> 8; 
        }
    }   
    printf("\033(B\033[%d;0H", x);
    return 0;
}

int bc_setbigcharpos (int * big, int x, int y, int value) {
    x--; y--;
    if (x < 0 || y < 0 || x > 7 || y > 7 || value < 0 || value > 1) return -1;    

    int index = (x < 4) ? 0 : 1;

    if (value == 1) 
        big[index] |= (1 << (y + (x % 4 * 8)));
    else 
        big[index] &= (~(1 << (y + (x % 4 * 8))));

    return 0;
}

int bc_getbigcharpos(int * big, int x, int y, int *value) {
    x--; y--;
    if (x < 0 || y < 0 || x > 7 || y > 7) return -1;  
    
    int index = (x < 4) ? 0 : 1;

    *value = big[index] >> (y + (x % 4 * 8)) & 0x1;

    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
    if (fd < 0 || count < 0) return -1;

    int result = write(fd, big, count * sizeof(int) * 2);
    if (result == count * sizeof(int) * 2) return 0;
    else return -1;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
    if (fd < 0 || need_count <= 0 || !count) return -1;

    int read_bytes = read(fd, big, need_count * sizeof(int) * 2);
    *count = read_bytes / (sizeof(int) * 2);

    if (read_bytes >= 0) return 0;
    else return -1;
}