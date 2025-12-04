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

int rollDice(){
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
    /*board[99] = 59;
    board[95] = 76;
    board[92] = 73;
    board[84] = 46;
    board[68] = 27;
    board[62] = 24;
    board[32] = 5;
    board[28] = 8;
    board[11] = 2;*/
}

void setName(struct PlayerName *name, int game_mode, char *input_player_one, char *input_player_two){
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

void saveGame(struct PlayerName *name, int save_option, int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode, int names_done){
    char name_files[32];
    snprintf(name_files, sizeof(name_files), "Game %d.txt", save_option);

    FILE *file = fopen(name_files, "w");
    if(file == NULL){
        perror("Error opening save file");
        return;
    }

    if(game_mode == 1){
        // formato: <game_mode> <player_one_name> <player_position_one>
        fprintf(file, "%d %d %s %d %d %s %d %d %d\n", game_mode, names_done, name->player_one_name, player_position_one, 0, "Friend_computer", 1, 0, 5);
        } else {
        // formato: <game_mode> <current_turn> <player_one_name> <player_position_one> <counter1> <player_two_name> <player_position_two> <counter2>
        fprintf(file, "%d %d %s %d %d %s %d %d %d\n", game_mode, names_done, name->player_one_name, player_position_one, counter_dice_condition_one, name->player_two_name, player_position_two, counter_dice_condition_two, current_turn);
    }
    fclose(file);
}

void loadGame(struct PlayerName *name, int *game_load, int *player_position_one, int *player_position_two, int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *game_mode, int *names_done){
    int temporal_game_mode;
    char name_files[32];
    int temp_cdco, temp_pp2, temp_cdct, temp_ct;
    char temp_pnt[20];

    snprintf(name_files, sizeof(name_files), "Game %d.txt", *game_load);

    FILE *file = fopen(name_files, "r");
    if(file == NULL){
        printf("Error loading file: %s\n", name_files);
        return;
    }

    if(fscanf(file, "%d", &temporal_game_mode) != 1){
        printf("Error leyendo el modo de juego\n");
        fclose(file);
        return;
    }
    *game_mode = temporal_game_mode;

    if(temporal_game_mode == 1){
        // después de leer el modo, quedan: <player_one_name> <player_position_one>
        if(fscanf(file, "%d %s %d %d %s %d %d %d", names_done, name->player_one_name, player_position_one, &temp_cdco, &temp_pnt, &temp_pp2, &temp_cdct, &temp_ct) != 8){
            printf("Error leyendo partida modo 1\n");
        }
    } else {
        // después del modo, quedan: <current_turn> <player_one_name> <player_position_one> <counter1> <player_two_name> <player_position_two> <counter2>
        if(fscanf(file, "%d %s %d %d %s %d %d %d", names_done, name->player_one_name, player_position_one, counter_dice_condition_one, name->player_two_name, player_position_two, counter_dice_condition_two, current_turn) != 8){
            printf("Error leyendo partida modo 2 o 3\n");
        } 
    }
    fclose(file);
} 