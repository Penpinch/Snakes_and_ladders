#ifndef LOGIC_H
#define LOGIC_H

struct PlayerName{
    char player_one_name[20];
    char player_two_name[20]; 
};

void initializeBoard(int board[], int board_size);

int rollDice();

int moveToken(int player_position, int num_dice);

void cheekSpecialCell(int board[]);

void setName(struct PlayerName *name, int game_mode, char *input_player_one, char *input_player_two);

void saveGame(struct PlayerName *name, int save_option, int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode, int names_done);

void loadGame(struct PlayerName *name, int *game_load, int *player_position_one, int *player_position_two, int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *game_mode, int *names_done);

#endif 