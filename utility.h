// utility.h
#ifndef UTILITY_H
#define UTILITY_H

#define BOARD_SIZE 4
#define WINNING_TILE 2048

void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
int place_random_tile(int board[BOARD_SIZE][BOARD_SIZE]);
void print_board(int board[BOARD_SIZE][BOARD_SIZE]);
int move_left(int board[BOARD_SIZE][BOARD_SIZE]);
int move_right(int board[BOARD_SIZE][BOARD_SIZE]);
int move_up(int board[BOARD_SIZE][BOARD_SIZE]);
int move_down(int board[BOARD_SIZE][BOARD_SIZE]);
int is_game_over(int board[BOARD_SIZE][BOARD_SIZE]);
int is_game_won(int board[BOARD_SIZE][BOARD_SIZE]);
char getch_unix();

#endif