// game2048.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    char input;
    
    srand(time(NULL));
    init_board(board);
    print_board(board);
    
    while (1) {
        input = getch_unix();
        
        int moved = 0;
        switch (input) {
            case 'a': moved = move_left(board); break;
            case 'd': moved = move_right(board); break;
            case 'w': moved = move_up(board); break;
            case 's': moved = move_down(board); break;
            case 'q': 
                printf("Game quit!\n");
                return 0;
        }
        
        if (moved) {
            place_random_tile(board);
        }
        
        print_board(board);
        
        if (is_game_won(board)) {
            printf("Congratulations! You reached 2048!\n");
            return 0;
        }
        
        if (is_game_over(board)) {
            printf("Game Over!\n");
            return 0;
        }
    }
    
    return 0;
}