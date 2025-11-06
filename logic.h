#ifndef LOGIC_H
#define LOGIC_H

void initializeBoard(int board[], int board_size);

int rollDice(char roll_dice);

int moveToken(int player_position, int num_dice);

void cheekSpecialCell(int board[]);

void showBoard(int display_board[], int board_size);

void saveGame(int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode);

void loadGame();

#endif