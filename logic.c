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
    board[99] = 59;
    board[95] = 76;
    board[92] = 73;
    board[84] = 64;
    board[68] = 34;
    board[67] = 25;
    board[45] = 37;
    board[28] = 8;
    board[20] = 2;
}

void showBoard(int display_board[], int board_size){
    for(int i = 1; i < board_size; i++){
        printf("%d\t", display_board[i]);
        if(i % 10 == 0){
            printf("\n");
        }
    }
}