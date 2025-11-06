#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

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

int moveToken(int player_position, int num_dice){
    return player_position += num_dice; 
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
    //board[99] = 59;
    //board[95] = 76;
    //board[92] = 73;
    //board[84] = 64;
    board[68] = 34;
    board[67] = 25;
    board[45] = 37;
    board[28] = 8;
    board[20] = 2;
}

void showBoard(int display_board[], int board_size){

    for(int row = 9; row >= 0; row--){
        for(int column = 1; column <= 10; column++){
            int index = row * 10 + column;
            printf("%3d\t", display_board[index]);
        }
        printf("\n\v");
    }
}

void saveGame(int player_position_one, int player_position_two, int current_turn, int counter_dice_condition_one, int counter_dice_condition_two, int game_mode){
    int game_option;
    FILE *game_1;
    FILE *game_2;
    FILE *game_3;
    FILE *game_4;

    game_1 = fopen("Partida 1.txt", "w");
    game_2 = fopen("Partida 2.txt", "w");
    game_3 = fopen("Partida 3.txt", "w");
    game_4 = fopen("Partida 4.txt", "w");

    printf("donde guardar: \n");
    scanf("%d", &game_option);

    if(game_1 != NULL && game_2 != NULL && game_3 != NULL && game_4 != NULL){
        switch (game_option){
            case 1:
                if(game_mode == 1){
                    fprintf(game_1, "Game mode: %d\n", game_mode);
                    fprintf(game_1, "Player position: %d\n ", player_position_one);
                } else {
                    fprintf(game_1, "Game mode: %d\n Current turn: %d\n", game_mode, current_turn);
                    fprintf(game_1, "Player position one: %d\n Dice counter one: %d\n", player_position_one, counter_dice_condition_one);
                    fprintf(game_1, "Player position two: %d\n Dice counter two: %d\n", player_position_two, counter_dice_condition_two);
                }
                break;

            case 2:
                if(game_mode == 1){
                    fprintf(game_2, "Game mode: %d\n", game_mode);
                    fprintf(game_2, "Player position: %d\n ", player_position_one);
                } else {
                    fprintf(game_2, "Game mode: %d\n Current turn: %d\n", game_mode, current_turn);
                    fprintf(game_2, "Player position one: %d\n Dice counter one: %d\n", player_position_one, counter_dice_condition_one);
                    fprintf(game_2, "Player position two: %d\n Dice counter two: %d\n", player_position_two, counter_dice_condition_two);
                }
                break;
            
            case 3:
                if(game_mode == 1){
                    fprintf(game_3, "Game mode: %d\n", game_mode);
                    fprintf(game_3, "Player position: %d\n ", player_position_one);
                } else {
                    fprintf(game_3, "Game mode: %d\n Current turn: %d\n", game_mode, current_turn);
                    fprintf(game_3, "Player position one: %d\n Dice counter one: %d\n", player_position_one, counter_dice_condition_one);
                    fprintf(game_3, "Player position two: %d\n Dice counter two: %d\n", player_position_two, counter_dice_condition_two);
                }
                break;

            case 4:
                if(game_mode == 1){
                    fprintf(game_4, "Game mode: %d\n", game_mode);
                    fprintf(game_4, "Player position: %d\n ", player_position_one);
                } else {
                    fprintf(game_4, "Game mode: %d\n Current turn: %d\n", game_mode, current_turn);
                    fprintf(game_4, "Player position one: %d\n Dice counter one: %d\n", player_position_one, counter_dice_condition_one);
                    fprintf(game_4, "Player position two: %d\n Dice counter two: %d\n", player_position_two, counter_dice_condition_two);
                }
                break;
        }
        fclose(game_1);
        fclose(game_2);
        fclose(game_3);
        fclose(game_4);

    } else {
        printf("Errrrrrror");
    }

}

void loadGame(){
    return;
}