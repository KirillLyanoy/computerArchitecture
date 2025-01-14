#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum colors {
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

int mt_clrscr (void) {
    printf("\E[H\E[2J");
    printf("\033[H");
    return 0;
}

int mt_gotoXY (int x, int y) {
    if (x < 0 || y < 0) 
        return -1;        
    printf("\033[%d;%dH", y, x);
    return 0;
}

int mt_getscreensize (int * rows, int * cols) {    
    if (rows == NULL || cols == NULL) return -1;
    else {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return 0;
    }
}

int mt_setfgcolor (enum colors color) {
    if (color < BLACK || color > DEFAULT) return -1;
    printf("\033[3%dm", color);
    return 0;
}

int mt_setbgcolor (enum colors color) {
    if (color < BLACK || color > DEFAULT) return -1;
    printf("\033[4%dm", color);
    return 0;
}