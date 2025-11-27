#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include <string.h>

void initializeBoard(int board[], int board_size){
    for(int i = 0; i < board_size; i++){
        board[i] = i;
    }
}

int rollDice(char roll_dice){
    if(roll_dice  == 'y'){
        return 1 + rand() % 6;
    } else {
        return 0;
    }
}

int rollDiceGraphic(){
    return 1 + rand() % 6;
}

int moveToken(int player_position, int num_dice){
    return player_position + num_dice; 
}

void cheekSpecialCell(int board[]){
    //Ladders
    board[3] = 22;
    board[6] = 16;
    board[14] = 56;
    board[17] = 36;
    board[29] = 48;
    board[31] = 52;
    board[44] = 78;
    board[55] = 74;
    board[75] = 96;

    //Snakes
    board[99] = 59;
    board[95] = 76;
    board[92] = 73;
    board[84] = 46;
    board[68] = 27;
    board[62] = 24;
    board[32] = 5;
    board[28] = 8;
    board[11] = 2;
}

void setName(struct PlayerName *name, int game_mode, const char *input_player_one, const char *input_player_two){
    switch (game_mode){
        case 1:
        case 3:
            strncpy(name -> player_one_name, input_player_one, sizeof(name -> player_one_name));
            name -> player_one_name[sizeof(name -> player_one_name) - 1] = '\0';
            break;
        case 2:
            strncpy(name -> player_one_name, input_player_one, sizeof(name -> player_one_name));
            name -> player_one_name[sizeof(name -> player_one_name) - 1] = '\0';

            strncpy(name -> player_two_name, input_player_two, sizeof(name -> player_two_name));
            name -> player_two_name[sizeof(name -> player_two_name) - 1] = '\0';
            break;
    }
}

void saveGame(const struct PlayerName *name, int save_option, int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode){
    char name_files[15];
    sprintf(name_files, "Game %d.txt", save_option);

    FILE *file = fopen(name_files, "w");

    if(file != NULL){
        if(game_mode == 1){
            //Game mode, Player name, Player position
            fprintf(file, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
        } else {
            //Game mode, Current turn, Player one name, Player position one, Dice counter one, Player two name, Player position two, Dice counter two
            fprintf(file, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
        }
        fclose(file);
    }

    /*    
    int game_option;
    FILE *game_1;
    FILE *game_2;
    FILE *game_3;
    FILE *game_4;

    game_1 = fopen("Game 1.txt", "w");
    game_2 = fopen("Game 2.txt", "w");
    game_3 = fopen("Game 3.txt", "w");
    game_4 = fopen("Game 4.txt", "w");

    if(game_1 != NULL && game_2 != NULL && game_3 != NULL && game_4 != NULL){

        switch (game_option){
            case 1:
                if(game_mode == 1){
                    //Game mode, Player name, Player position
                    fprintf(game_1, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
                } else {
                    //Game mode, Current turn, Player one name, Player position one, Dice counter one, Player two name, Player position two, Dice counter two
                    fprintf(game_1, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
                }
                break;

            case 2:
                if(game_mode == 1){
                    fprintf(game_2, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
                } else {
                    fprintf(game_2, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
                }
                break;
            
            case 3:
                if(game_mode == 1){
                    fprintf(game_3, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
                } else {
                    fprintf(game_3, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
                }
                break;

            case 4:
                if(game_mode == 1){
                    fprintf(game_4, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
                } else {
                    fprintf(game_4, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
                }
                break;
        }
        fclose(game_1);
        fclose(game_2);
        fclose(game_3);
        fclose(game_4);

    } else {
        printf("Error opening file.");
    }
*/
}

void loadGame(const struct PlayerName *name, int game_load, int *player_position_one, int *player_position_two, int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *game_mode){
    int temporal_game_mode;
    char name_files[15];

    sprintf(name_files, "Game %d.txt", game_load);

    FILE *file = fopen(name_files, "r");
    if(file == NULL){
        printf("Error loadinf file.");
        return;
    }
    fscanf(file, "%d", &temporal_game_mode);

    if(temporal_game_mode == 1){
        fscanf(file, "%d %s %d", game_mode, name -> player_one_name, player_position_one);
    } else {
        fscanf(file, "%d %d %s %d %d %s %d %d", game_mode, current_turn, name -> player_one_name, player_position_one, counter_dice_condition_one, name -> player_two_name, player_position_two, counter_dice_condition_two);
    }
    fclose(file);
} 