// utility.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include "utility.h"

void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    place_random_tile(board);
    place_random_tile(board);
}

int place_random_tile(int board[BOARD_SIZE][BOARD_SIZE]) {
    int empty = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) empty++;
        }
    }
    
    if (empty == 0) return 0;
    
    int position = rand() % empty;
    int count = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                count++;
                if (count == position) {
                    board[i][j] = (rand() % 2 == 0) ? 2 : 4;
                    return 1;
                }
            }
        }
    }
    return 1;
}

void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("\n2048 Game\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) printf("%4s ", " ");
            else printf("%4d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\nUse w,a,s,d to move, q to quit\n");
}

static int merge_row(int row[BOARD_SIZE]) {
    int moved = 0;
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
            moved = 1;
        }
    }
    return moved;
}

static int shift_row(int row[BOARD_SIZE]) {
    int moved = 0;
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        if (row[i] == 0 && row[i + 1] != 0) {
            row[i] = row[i + 1];
            row[i + 1] = 0;
            moved = 1;
        }
    }
    return moved;
}

int move_left(int board[BOARD_SIZE][BOARD_SIZE]) {
    int moved = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        int row[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) row[j] = board[i][j];
        
        for (int k = 0; k < BOARD_SIZE; k++) {
            moved |= shift_row(row);
            moved |= merge_row(row);
            moved |= shift_row(row);
        }
        
        for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = row[j];
    }
    return moved;
}

int move_right(int board[BOARD_SIZE][BOARD_SIZE]) {
    int moved = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        int row[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) row[j] = board[i][BOARD_SIZE - 1 - j];
        
        for (int k = 0; k < BOARD_SIZE; k++) {
            moved |= shift_row(row);
            moved |= merge_row(row);
            moved |= shift_row(row);
        }
        
        for (int j = 0; j < BOARD_SIZE; j++) board[i][BOARD_SIZE - 1 - j] = row[j];
    }
    return moved;
}

int move_up(int board[BOARD_SIZE][BOARD_SIZE]) {
    int moved = 0;
    for (int j = 0; j < BOARD_SIZE; j++) {
        int col[BOARD_SIZE];
        for (int i = 0; i < BOARD_SIZE; i++) col[i] = board[i][j];
        
        for (int k = 0; k < BOARD_SIZE; k++) {
            moved |= shift_row(col);
            moved |= merge_row(col);
            moved |= shift_row(col);
        }
        
        for (int i = 0; i < BOARD_SIZE; i++) board[i][j] = col[i];
    }
    return moved;
}

int move_down(int board[BOARD_SIZE][BOARD_SIZE]) {
    int moved = 0;
    for (int j = 0; j < BOARD_SIZE; j++) {
        int col[BOARD_SIZE];
        for (int i = 0; i < BOARD_SIZE; i++) col[i] = board[BOARD_SIZE - 1 - i][j];
        
        for (int k = 0; k < BOARD_SIZE; k++) {
            moved |= shift_row(col);
            moved |= merge_row(col);
            moved |= shift_row(col);
        }
        
        for (int i = 0; i < BOARD_SIZE; i++) board[BOARD_SIZE - 1 - i][j] = col[i];
    }
    return moved;
}

int is_game_over(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) return 0;
            if (i < BOARD_SIZE - 1 && board[i][j] == board[i + 1][j]) return 0;
            if (j < BOARD_SIZE - 1 && board[i][j] == board[i][j + 1]) return 0;
        }
    }
    return 1;
}

int is_game_won(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == WINNING_TILE) return 1;
        }
    }
    return 0;
}

char getch_unix() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Gets the current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}