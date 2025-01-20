#include "myBigChars.h"
#include "myReadkey.h"
#include "myTerm.h"
#include "simple_computer.h"

int draw_console(int *rows, int *cols) {
    mt_clrscr();
    mt_getscreensize(rows, cols);

    bc_box(1, 1, 12, 61);

    bc_box(1, 63, 3, 30);
    bc_box(4, 63, 3, 30);
    bc_box(7, 63, 3, 30);
    bc_box(10, 63, 3, 30);

    bc_box(13, 1, 10, 42);
    bc_box(13, 44, 10, 49);

    mt_gotoXY (29, 1); printf("Memory");
    mt_gotoXY (72, 1); printf("accumulator");
    mt_gotoXY (70, 4); printf("instructionCounter");
    mt_gotoXY (73, 7); printf("Operation");
    mt_gotoXY (75, 10); printf("Flags");
    mt_gotoXY (50, 13); printf("Keys:");

    mt_gotoXY (46, 14); printf(" l - load");
    mt_gotoXY (46, 15); printf(" s - save");
    mt_gotoXY (46, 16); printf(" r - run");
    mt_gotoXY (46, 17); printf(" t - step");
    mt_gotoXY (46, 18); printf(" i - reset");
    mt_gotoXY (46, 19); printf(" F5 - accumulator");
    mt_gotoXY (46, 20); printf(" F6 - instructionCounter");

    mt_gotoXY (0, 23);
    return 0;
}

int print_big_chars(int value) {
    
    int x = 14, y = 2;

    int digits[4];

    digits[0] = value / 1000;
    digits[1] = value / 100 - value / 1000 * 10;
    digits[2] = value / 10 - value / 100 * 10;
    digits[3] = value - value / 10 * 10;

    int big_symbol_0[2] = { BIG_SYMBOL_0 };
    int big_symbol_1[2] = { BIG_SYMBOL_1 };
    int big_symbol_2[2] = { BIG_SYMBOL_2 };
    int big_symbol_3[2] = { BIG_SYMBOL_3 };
    int big_symbol_4[2] = { BIG_SYMBOL_4 };
    int big_symbol_5[2] = { BIG_SYMBOL_5 };
    int big_symbol_6[2] = { BIG_SYMBOL_6 };
    int big_symbol_7[2] = { BIG_SYMBOL_7 };
    int big_symbol_8[2] = { BIG_SYMBOL_8 };
    int big_symbol_9[2] = { BIG_SYMBOL_9 };

    for (int i = 0; i < 4; i++) {
        switch (digits[i]) {
            case (0): {           
                bc_printbigchar(big_symbol_0, x, y, DEFAULT, DEFAULT);                
                break; 
            };            
            case (1): { 
                bc_printbigchar(big_symbol_1, x, y, DEFAULT, DEFAULT); 
                break; 
            }
            case (2): { 
                bc_printbigchar(big_symbol_2, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (3): { 
                bc_printbigchar(big_symbol_3, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (4): { 
                bc_printbigchar(big_symbol_4, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (5): { 
                bc_printbigchar(big_symbol_5, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (6): { 
                bc_printbigchar(big_symbol_6, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (7): { 
                bc_printbigchar(big_symbol_7, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (8): { 
                bc_printbigchar(big_symbol_8, x, y, DEFAULT, DEFAULT); 
                break; 
            }  
            case (9): { 
                bc_printbigchar(big_symbol_9, x, y, DEFAULT, DEFAULT); 
                break; 
            }           
            
            default: return -1;
        }
        y += 8;
    }
    return 0;
}

int print_memory(int sc_memory[], int selected_cell_index) {
    if (sc_memory == NULL) return -1;

    int x = 2, y = 2;
    int command, operand, value;

    for (int i = 0; i < 100; i+=10) {
        mt_gotoXY(x, y);
        for (int j = 0; j < 10; j++) {
            sc_memoryGet(i + j, &value);

            if (selected_cell_index == i + j) {
                mt_setfgcolor(BLACK);
                mt_setbgcolor(WHITE);
                printf("+%04d", sc_commandDecode(value, &command, &operand));
                print_big_chars(value);
                mt_setbgcolor(DEFAULT);
                mt_setfgcolor(DEFAULT);
                printf(" ");
            }
            else printf("+%04d ", sc_commandDecode(value, &command, &operand));

        }
        printf("\n");
        y +=1; 
        x = 2;  
    }
    mt_gotoXY (0, 24);
    return 0;
}

int memory_cell_selection (keys direction, int* selected_cell_index) {
    switch (direction) {
        case(KEY_UP):            
            if (0 <= *selected_cell_index - 10) *selected_cell_index -= 10;
            return 0;
        case(KEY_DOWN):
            if (*selected_cell_index + 10 < memory_size) *selected_cell_index += 10;
            return 0;
        case(KEY_LEFT):
            if (0 <= *selected_cell_index - 1) *selected_cell_index -= 1;
            return 0;  
        case(KEY_RIGHT):
            if (*selected_cell_index + 1 < memory_size) *selected_cell_index += 1;
            return 0;         
        default: 
            return -1;    
    }
}

int main() {
    rk_mytermsave();

    int rows, cols;
    int selected_cell_index = 0;
    keys key;
    rk_mytermregime(0, 0, 1, 0, 1);
    sc_memoryInit();

    while(true) {
        draw_console(&rows, &cols);
        print_memory(sc_memory, selected_cell_index);

        rk_readkey(&key);
        if (37 <= key <= 40) memory_cell_selection(key, &selected_cell_index);

    }

    rk_mytermrestore();
    return 0;
}