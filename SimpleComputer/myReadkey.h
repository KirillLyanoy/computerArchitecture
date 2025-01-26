#pragma once

#include <unistd.h>
#include <termios.h>

enum keys {
    KEY_I = 9, KEY_L = 12, KEY_R = 18, KEY_S = 19, KEY_T = 20,

    KEY_1 = 27, KEY_2 = 28, KEY_3 = 29, KEY_4 = 30, KEY_5 = 31, KEY_6 = 32, KEY_7 = 33, KEY_8 = 34, KEY_9 = 35, KEY_0 = 36,

    KEY_UP = 37, KEY_DOWN = 38, KEY_LEFT = 39, KEY_RIGHT = 40, 

    KEY_F5 = 41, KEY_F6 = 42,    
};

int rk_readkey (enum keys *key) {
    char read_keys[8];

    int num_read = read(0, read_keys, sizeof(read_keys)) - 1;

    if (num_read < 0) return -1;
    else {
        if (num_read == 0) {
            switch (read_keys[0]) {
                case 'i': *key = KEY_I; return 0;
                case 'l': *key = KEY_L; return 0;
                case 'r': *key = KEY_R; return 0;
                case 's': *key = KEY_S; return 0;
                case 't': *key = KEY_T; return 0;
                case '0': *key = KEY_0; return 0;
                case '1': *key = KEY_1; return 0;
                case '2': *key = KEY_2; return 0;
                case '3': *key = KEY_3; return 0;
                case '4': *key = KEY_4; return 0;
                case '5': *key = KEY_5; return 0;
                case '6': *key = KEY_6; return 0;
                case '7': *key = KEY_7; return 0;
                case '8': *key = KEY_8; return 0;
                case '9': *key = KEY_9; return 0;
                default: 
                    return -1;
            }
        }
        else { if (num_read == 2) {
                switch (read_keys[2]) {
                    case ('A'):
                        *key = KEY_UP;
                        return 0;
                    case ('B'):
                        *key = KEY_DOWN;
                        return 0;
                    case ('C'):
                        *key = KEY_RIGHT;
                        return 0;
                    case ('D'):
                        *key = KEY_LEFT;
                        return 0;
                    default: 
                        return -1;
                }
            }
            else {
                switch (read_keys[3]) {
                    case('5'):
                        *key = KEY_F5;
                        return 0;
                    case('6'):
                        *key = KEY_F6;
                        return 0;
                    default:
                        return -1;
                }
            }
        }
    }
    return 0;
} 

static struct termios original_term;

int rk_mytermsave(void) {
    tcgetattr(0, &original_term);  
    return 0;
}

int rk_mytermrestore(void) {
    return tcsetattr(0, TCSANOW, &original_term); 
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int
sigint) {
    struct termios options;

    if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
    if (regime == 1) options.c_lflag |= ICANON;
	else 
        if (regime == 0) options.c_lflag &= ~ICANON;
	    else 
            return -1;
    if (regime == 0) {
		options.c_cc[VTIME] = vtime;
		options.c_cc[VMIN] = vmin;
		if (echo == 1)
			options.c_lflag |= ECHO;
		else
			if (echo == 0)
				options.c_lflag &= ~ECHO;
			else
				return -1;
		if (sigint == 1)
			options.c_lflag |= ISIG;
		else
			if (sigint == 0)
				options.c_lflag &= ~ISIG;
			else
				return -1;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &options) != 0)
		return -1;
    return 0;
}