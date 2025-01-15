#include <iostream>
#include <unistd.h>
#include "myTerm.h"

int main()
{
    std::cout << "Hello World!";

    mt_clrscr();

    mt_gotoXY(5, 5);


    int cols, rows;
    mt_getscreensize(&cols, &rows);
    printf("Cols: %d, Rows: %d\n", cols, rows);

    mt_setfgcolor(RED);
    mt_setbgcolor(GREEN);
    printf("Colored text\n");

    mt_setbgcolor(DEFAULT);
    mt_setfgcolor(DEFAULT);
}
