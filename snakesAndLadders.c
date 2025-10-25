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

void showBoard(int on_screen_board[], int board_size){
    for(int i = 1; i < board_size; i++){
        printf("%d\t", on_screen_board[i]);
        if(i % 10 == 0){
            printf("\n");
        }
    }
}

/*int save_game(){}
int load_gamme(){}*/

int main(){
    int game_on = 1;//control
    srand(time(NULL));

    int num_dice, player_position = 1;    
    int logic_board[101], on_screen_board[101];
    int board_size = sizeof(logic_board) / sizeof(logic_board[0]);
    int counter_dice_condition;
    
    //initialize the board.
    initializeBoard(on_screen_board, board_size);
    initializeBoard(logic_board, board_size);
    cheekSpecialCell(logic_board);

    while(game_on == 1){
        char roll_dice = 'n';

        //Show the board on screen.
        showBoard(on_screen_board, board_size);

        //Rolling the dice.
        printf("Roll the dice('y' for yes)?: ");
        scanf(" %c", &roll_dice);
        
        //clear the screen.
        system("cls");//fputs("\033[2J\033[H", stdout);

        num_dice = rollDice(roll_dice);
        printf("Dice result: %d\n", num_dice);

        //Show the player position.
        printf("Last position: %d\n", player_position);
        player_position = moveToken(player_position, num_dice);
        player_position = logic_board[player_position];

        //cheek if extra turn or reload
        if(num_dice == 6){//falta turno extra
            counter_dice_condition += 1;
            printf("contador valor: %d\n", counter_dice_condition);
            if(counter_dice_condition == 3){
                counter_dice_condition = 0;
                player_position = logic_board[1];
            }
        } else {
            counter_dice_condition = 0;
            printf("contador valor: %d\n", counter_dice_condition);
        }

        if(player_position >= 100){
            player_position = 100;
            printf("You won!");
            break;
        }
        printf("New position: %d\n", player_position);
    }
    
    return 0;
}