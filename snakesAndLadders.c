# include "raylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "logic.h"
# include <string.h>
# include "grid.h" 

//gcc snakesAndLadders.c logic.c grid.c -o nolesabemos -lraylib -lopengl32 -lgdi32 -mconsole

void playerTurn(
    int display_board[], int logic_board[], int board_size, int enable_dice, int *num_dice, 
    int *player_position, int *counter_dice_condition, int *curren_turn, int *game_on){
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

    //Victory check
    if(*player_position >= 100){
        *player_position = 100;
        printf("%d\n", *player_position);
        printf("You won!\n");
        system("pause");
        *game_on = 0;
        return;
    }
    *player_position = logic_board[*player_position];

    //cheek if extra turn or restart
    if(*num_dice == 6){
        *counter_dice_condition += 1;
        (*counter_dice_condition < 2) ? *curren_turn -= 1 : (void)0;
        printf("contador valor: %d\n", *counter_dice_condition);
        if(*counter_dice_condition == 3){
            *counter_dice_condition = 0;
            *player_position = logic_board[1];
        }
    } else {
        *counter_dice_condition = 0;
        printf("contador valor: %d\n", *counter_dice_condition);
    }

    printf("New position: %d\n", *player_position);

    //upload board
    showBoard(display_board, board_size);
    system("pause");
}

int main(){
    
    //Graphics variables. DO NOT TOUCH
    int cellsize = 60;
    Grid g;

    //Color darkBlue = {44, 44, 127, 255};
    Grid_init(&g, cellsize);//inicializa la estructura grid

    const int screenwidth = g.columns * g.cellsize;//ancho y alto de la pantalla, se calcula con la cantidad de filas/columans multiplicadas por el tamaño de cada una
    const int screenheight = g.rows * g.cellsize;
    char texto[50];

    InitWindow(screenwidth+150, screenheight+150, "Snakes And Ladderrs"); // ventana de inicializacion
    SetTargetFPS(60);

    while(!WindowShouldClose()){//mantiene la ventana abierta
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        showGrid(&g, cellsize, screenwidth, screenheight, texto);

        EndDrawing();
    }

    CloseWindow();//cierra la ventana 
//-------------------

    int game_on = 1;//control
    srand(time(NULL));

    int game_mode = 0, enable_dice = 1, game_load;
    struct PlayerName name = {"", "Computer friend"};
    
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
    while(getchar() != '\n');

    //initialize the board.
    initializeBoard(display_board, board_size);
    initializeBoard(logic_board, board_size);
    cheekSpecialCell(logic_board);

    switch (game_mode){
        case 1:
            setName(&name, game_mode);
            while(game_on == 1){
                system("cls");
                printf("%s.\n", name.player_one_name);
                playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
            }
            break;
        case 2:
            setName(&name, game_mode);
            while(game_on == 1){
                if(current_turn % 2 == 0){
                    system("cls");
                    printf("%s.\n", name.player_two_name);
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_two, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on);
                } else {
                    system("cls");
                    printf("%s.\n", name.player_one_name);
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
                }
                current_turn += 1; 
            }
            break;
        case 3:
            setName(&name, game_mode);
            while(game_on == 1){
                if(current_turn % 2 == 0){
                    system("cls");
                    enable_dice = 0;
                    printf("%s.\n", name.player_two_name);
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_two, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on);
                } else {
                    system("cls");
                    enable_dice = 1;
                    printf("%s.\n", name.player_one_name);
                    playerTurn(display_board, logic_board, board_size, enable_dice, &num_dice_one, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
                }
                current_turn += 1; 
            }   
            break;
        default:
            printf("Invalid mode. ");
            exit(EXIT_FAILURE);
            break;
    }
    saveGame(&name, player_position_one, player_position_two, current_turn, counter_dice_condition_one, counter_dice_condition_two, game_mode);
    printf("Game to load: ");
    scanf("%d", &game_load);
    loadGame(&name, game_mode, &player_position_one, &player_position_two, &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &game_mode);

    return 0;
}