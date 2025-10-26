# include <stdio.h>
# include <stdlib.h>
# include <time.h>

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

void playerTurn(int display_board[], int logic_board[], int board_size, int enable_dice, int *num_dice, int *player_position, int *counter_dice_condition){
    char roll_dice = 'n';

    //Show the board on screen.
    showBoard(display_board, board_size);

    //Rolling the dice.
    if(enable_dice == 1){
        printf("Roll the dice('y' for yes)?: ");
        scanf(" %c", &roll_dice);            
    } else {
        roll_dice = 'y';
    }

    //clear the screen.
    system("cls");//fputs("\033[2J\033[H", stdout);

    *num_dice = rollDice(roll_dice);
    printf("Dice result: %d\n", *num_dice);

    //Show the player position.
    printf("Last position: %d\n", *player_position);
    *player_position = moveToken(*player_position, *num_dice);
    *player_position = logic_board[*player_position];

    //cheek if extra turn or restart
    if(*num_dice == 6){//falta turno extra
        *counter_dice_condition += 1;
        printf("contador valor: %d\n", *counter_dice_condition);
        if(*counter_dice_condition == 3){
            *counter_dice_condition = 0;
            *player_position = logic_board[1];
        }
    } else {
        *counter_dice_condition = 0;
        printf("contador valor: %d\n", *counter_dice_condition);
    }

    if(*player_position >= 100){
        *player_position = 100;
        printf("You won!");
        exit(EXIT_SUCCESS);
    }
    printf("New position: %d\n", *player_position);

    //upload board
    showBoard(display_board, board_size);
    system("pause");
}

/*int save_game(){}
int load_gamme(){}*/

int main(){
    int game_on = 1;//control
    srand(time(NULL));

    int game_mode = 0, enable_dice = 1;
    int num_dice_one = 0, player_position_one = 1, counter_dice_condition_one = 0;   
    int num_dice_two = 0, player_position_two = 1, counter_dice_condition_two = 0;     
    int logic_board[101], display_board[101];
    int board_size = sizeof(logic_board) / sizeof(logic_board[0]);
    int current_turn = 1;

    printf("Snakes and ladders.\n");
    printf("Welcome!\n\n");

    printf("Game mode: \n");
    printf("1. practice.\n");
    printf("2. 2 players.\n");
    printf("3. against the computer. \n");
    scanf("%d", &game_mode);

    //initialize the board.
    initializeBoard(display_board, board_size);
    initializeBoard(logic_board, board_size);
    cheekSpecialCell(logic_board);

    switch (game_mode){
        case 1:
            while(game_on == 1){
                system("cls");
                printf("Player x.\n");
                playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one);
            }
            break;
        case 2:
            while(game_on == 1){
                if(current_turn % 2 == 0){
                    system("cls");
                    printf("Player 2.\n");
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_two, &player_position_two, &counter_dice_condition_two);
                } else {
                    system("cls");
                    printf("Player 1.\n");
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one);
                }
                current_turn += 1; 
            }
            break;
        case 3:
            while(game_on == 1){
                if(current_turn % 2 == 0){
                    system("cls");
                    enable_dice = 0;
                    printf("Computer.\n");
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_two, &player_position_two, &counter_dice_condition_two);
                } else {
                    system("cls");
                    enable_dice = 1;
                    printf("Player x.\n");
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one);
                }
                current_turn += 1; 
            }
            break;
        default:
            printf("Invalid mode. ");
            break;
    }
    
    return 0;
}