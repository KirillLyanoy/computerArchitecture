#include "myBigChars.h"
#include "myReadkey.h"
#include "myTerm.h"
#include "simple_computer.h"

int draw_console(int *rows, int *cols) {
    mt_clrscr();
    mt_getscreensize(rows, cols);


    bc_box(1, 1, *rows * 7 / 10, *cols * 8 / 10);

    bc_box(1, *cols * 8 / 10 + 2, 3, *cols * 2 / 10 - 1);
    bc_box(1, *cols * 8 / 10 + 2, 3, *cols * 2 / 10 - 1);
    bc_box(1, *cols * 8 / 10 + 2, 3, *cols * 2 / 10 - 1);
    bc_box(1, *cols * 8 / 10 + 2, 3, *cols * 2 / 10 - 1);
    
    return 0;
}

int main() {
    int rows, cols;

    draw_console(&rows, &cols);


    return 0;
}