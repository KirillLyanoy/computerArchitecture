#include <stdio.h>
#include <unistd.h>
#include "myBigChars.h"
#include "myReadkey.h"
#include "myTerm.h"
#include "simple_computer.h"


int print_accumulator(int accumulator) {    
    mt_gotoXY (75, 2); printf("+%04d", accumulator);
    mt_gotoXY (0, 23);
    return 0;
}

int print_instructionCounter(int selected_cell_index) {
    if (selected_cell_index < 0 || selected_cell_index > 99) return -1;

    //mt_gotoXY (75, 5); printf("+%04x", selected_cell_index);
    mt_gotoXY (77, 5); printf("%d", selected_cell_index);
    mt_gotoXY (0, 23);
    return 0;
}

int set_instructionCounter(int *selected_cell_index) {
    int ic;
    
    rk_mytermrestore();
    printf("Memory address: ");
    scanf("%d", &ic);
    rk_mytermregime(0, 0, 1, 0, 1);
    if (ic < 0 || ic > 99) return -1;

    *selected_cell_index = ic;
    return 0; 
}

int set_accumulator(int *accumulator) {
    int acc;
    
    rk_mytermrestore();
    printf("Accumulator value: ");
    scanf("%d", &acc);
    rk_mytermregime(0, 0, 1, 0, 1);
    if (acc < 0 || acc > 9999) return -1;

    *accumulator = acc;
    return 0; 
}

int print_operation() {
    return 0;
}

int print_flags(void) {
    int value;
    int y = 73;
    for (int i = 1; i <= REGISTER_SIZE; i++) {
        sc_regGet(i, &value);
        mt_gotoXY (y, 11); 
        char c;

        switch (i) {
            case 1:
                c = 'M';
                break;
            case 2:
                c = 'E';
                break;
            case 3:
                c = '0';
                break;  
            case 4:
                c = 'P';
                break;
            case 5:
                c = 'T';
                break;
            default: 
                return -1;
        }
        if (value) {
            printf("%c ", c);
            y += 2;
        }
    }
    mt_gotoXY (0, 23);
    return 0;
}

int draw_console(int *rows, int *cols) {    
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
    mt_gotoXY (0, 24);
    return 0;
}

int print_big_chars(int value) {
    
    int x = 14, y = 10;
    int digits[4] { value / 1000,
                    value / 100 - value / 1000 * 10,
                    value / 10 - value / 100 * 10,
                    value - value / 10 * 10 };

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
    int big_symbol_plus[2] = { BIG_SYMBOL_PLUS };   

    bc_printbigchar(big_symbol_plus, x, 2, DEFAULT, DEFAULT); 
    
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
    int command, operand, value, selected_cell_value;
    for (int i = 0; i < 100; i+=10) {
        mt_gotoXY(x, y);
        for (int j = 0; j < 10; j++) {
            sc_memoryGet(i + j, &value);
            if (selected_cell_index == i + j) {
                mt_setfgcolor(BLACK);
                mt_setbgcolor(WHITE);
                printf("+%04d", sc_commandDecode(value, &command, &operand));
                selected_cell_value = value;
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
    print_big_chars(selected_cell_value);
       
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
    int accumulator = 0;

    int selected_cell_index = 0;
    keys key;
    rk_mytermregime(0, 0, 1, 0, 1);
    sc_memoryInit();
    char file[] = "memory.txt";

    while(true) {
        mt_clrscr();

        draw_console(&rows, &cols);
        print_memory(sc_memory, selected_cell_index);
        print_accumulator(accumulator);
        print_instructionCounter(selected_cell_index);
        //print_operation();
        print_flags();
        
        fflush(stdout);

        rk_readkey(&key);

        switch(key) {
            case (37): //up
                memory_cell_selection(key, &selected_cell_index); break;
            case (38): //down
                memory_cell_selection(key, &selected_cell_index); break;
            case (39): //left
                memory_cell_selection(key, &selected_cell_index); break;
            case (40): //right
                memory_cell_selection(key, &selected_cell_index); break;
            case (9): //i 
                sc_memorySave(file); break;
            case (12): //l 
                sc_memorySave(file); break;
            case (18): //r 
                break;
            case (19): //s 
                break;
            case (20): //t 
                break;
            case (41): //f5                
                set_accumulator(&accumulator); break;
            case (42): //f6
                set_instructionCounter(&selected_cell_index); break;
            default: break;
        }

        if (37 <= key <= 40) memory_cell_selection(key, &selected_cell_index);
    }
    rk_mytermrestore();
    return 0;
}