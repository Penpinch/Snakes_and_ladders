#ifndef LOGIC_H
#define LOGIC_H

void initializeBoard(int board[], int board_size);

int rollDice(char roll_dice);

int moveToken(int player_position, int num_dice);

void cheekSpecialCell(int board[]);

void showBoard(int display_board[], int board_size);

#endif