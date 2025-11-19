#ifndef LOGIC_H
#define LOGIC_H

struct PlayerName{
    char player_one_name[20];
    char player_two_name[20]; 
};

void initializeBoard(int board[], int board_size);

int rollDice(char roll_dice);

int moveToken(int player_position, int num_dice);

void cheekSpecialCell(int board[]);

void showBoard(int display_board[], int board_size);

void setName(struct PlayerName *name, int game_mode);

void saveGame(const struct PlayerName *name, int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode);

void loadGame(const struct PlayerName *name, int game_load, int *player_position_one, int *player_position_two, int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *game_mode);

#endif