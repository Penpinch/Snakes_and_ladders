# include "raylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "logic.h"
# include <string.h>
# include "grid.h" 

//gcc snakesAndLadders.c logic.c grid.c -o q -lraylib -lopengl32 -lgdi32 -mconsole

void playerTurn(
    int logic_board[], int board_size, int enable_dice, int *num_dice, 
    int *player_position, int *counter_dice_condition, int *curren_turn, int *game_on){
    //char roll_dice = 'n';

    *player_position = moveToken(*player_position, *num_dice);
    printf("%d", *player_position);

    //Victory check
    if(*player_position >= 100){
        *player_position = 100;
        DrawText("You won!", 500, 500, 30, RED);
        WaitTime(5.0);
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
        *curren_turn += 1;
    }

    printf("New position: %d\n\n", *player_position);

    /*if(enable_dice == 1){
        roll_dice = GetKeyPressed();           
    } else {
        roll_dice = 'y';
    }
*/
    
/*
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
    //showBoard(display_board, board_size);
    system("pause");
    */
}

int capturePlayerName(
    char *temporal_buffer_player_one, char *temporal_buffer_player_two, 
    int *writing_player_one, int *writing_player_two, int game_mode){
    
    static int cursor1 = 0;
    static int cursor2 = 0;

    if(*writing_player_one){
        int key = GetCharPressed();

        while(key > 0){
            if(key >= 32 && key <= 125 && cursor1 <19){
                temporal_buffer_player_one[cursor1++] = (char)key;
                temporal_buffer_player_one[cursor1] = '\0';
            }
            key = GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE) && cursor1 > 0){
            cursor1--;
            temporal_buffer_player_one[cursor1] = '\0';
        }
        if(IsKeyPressed(KEY_ENTER)){
            *writing_player_one = 0;

            if(game_mode == 2){
                cursor1 = 0;
                cursor2 = 0;
                *writing_player_one = 0;
                memset(temporal_buffer_player_two, 0, 20);
                *writing_player_two = 1;
            } else {
                return 1;
            }
        }
        return 0;
    }

    if(*writing_player_two){
        int key = GetCharPressed();

        while(key > 0){
            if(key >= 32 && key <= 125 && cursor2 <19){
                temporal_buffer_player_two[cursor2++] = (char)key;
                temporal_buffer_player_two[cursor2] = '\0';
            }
            key = GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE) && cursor2 > 0){
            cursor2--;
            temporal_buffer_player_two[cursor2] = '\0';
        }
        if(IsKeyPressed(KEY_ENTER)){
            *writing_player_two = 0;
            cursor2 = 0;
            return 1;
        }
    }
    return 0;
}

int main(){
    //Logic variables. do not touch.
    srand(time(NULL));

    int game_on = 1;//control
    int game_mode = 2, enable_dice = 1, game_load; //pruebas
    struct PlayerName name = {"", "Computer friend"};

    int player_position_one = 1, counter_dice_condition_one = 0;   
    int player_position_two = 1, counter_dice_condition_two = 0;     
    int logic_board[101];
    int board_size = sizeof(logic_board) / sizeof(logic_board[0]);
    int current_turn = 1, dice_was_rolled = 0, dice_value = 0;

    initializeBoard(logic_board, board_size); 
    cheekSpecialCell(logic_board);
    
    //Graphics variables. DO NOT TOUCH
    const int screenwidth = 1000;
    const int screenheight = 1000;

    char temporal_buffer_player_one[20] = {0};
    char temporal_buffer_player_two[20] = {0};
    int writing_player_one = 1;
    int writing_player_two = 0;
    int names_done = 0;

    InitWindow(screenwidth, screenheight, "Snakes And Ladders"); // ventana de inicializacion
    SetTargetFPS(60);
    Texture2D grid_image;
    grid_image = LoadTexture("Grid_image.png");
    Texture2D dicetextures[6]; //inicializa las imagenes del dado
    dicetextures[0] = LoadTexture("Dice_faces/DiceFace1.png");
    dicetextures[1] = LoadTexture("Dice_faces/DiceFace2.png");
    dicetextures[2] = LoadTexture("Dice_faces/DiceFace3.png");
    dicetextures[3] = LoadTexture("Dice_faces/DiceFace4.png");
    dicetextures[4] = LoadTexture("Dice_faces/DiceFace5.png");
    dicetextures[5] = LoadTexture("Dice_faces/DiceFace6.png");

    temporal_buffer_player_one[0] = '\0';
    temporal_buffer_player_two[0] = '\0';
    while(!WindowShouldClose()){

        if(names_done == 0){
            int captura = capturePlayerName(temporal_buffer_player_one, temporal_buffer_player_two, &writing_player_one, &writing_player_two, game_mode);

            BeginDrawing();
            ClearBackground(RAYWHITE);
            if(writing_player_one){
                DrawText("Player 1 name: ", 50, 50, 30, BLACK);
                DrawText(temporal_buffer_player_one, 50, 100, 30, DARKPURPLE);
            }
            if(writing_player_two){
                DrawText("Player 2 name: ", 50, 50, 30, BLACK);
                DrawText(temporal_buffer_player_two, 50, 100, 30, DARKPURPLE);
            }
            EndDrawing();
            if(captura == 1){
                names_done = 1;
            }
            continue;
        }
        
        if(names_done == 1){
            names_done = 2;
            const char *p2 = (game_mode == 2) ? temporal_buffer_player_two : "";
            setName(&name, game_mode, temporal_buffer_player_one, p2);
        }

        if(IsKeyPressed(KEY_SPACE) && enable_dice == 1 && dice_was_rolled == 0){
            dice_value = rollDiceGraphic();//toma el valor del dado
            dice_was_rolled = 1;
            printf("sapce presed -> dice value = %d\n", dice_value);
            fflush(stdout);
        }

        BeginDrawing();
        ClearBackground(BLUE);

        DrawTexture(grid_image, 0, 0, WHITE);
        DrawText("Press space key to roll the dice.", 250, 40, 30, BLACK);
        DrawDice(dice_value, dicetextures); //dibuja el dado
        DrawText(name.player_one_name, 300, 760, 30, BLACK); 
        if(game_mode != 1){
            DrawText(name.player_two_name, 300, 860, 30, BLACK);
        }

        switch (game_mode){
            case 1:
                if(dice_was_rolled == 1){
                    playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
                    dice_was_rolled = 0;
                }
                break;
            case 2:
                if(dice_was_rolled == 1){
                    if(current_turn % 2 == 0){
                        playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on);
                    } else {
                        playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
                    }
                    dice_was_rolled = 0;
                }
                break;
            case 3:
                if(dice_was_rolled == 1){
                    if(current_turn % 2 == 0){
                        enable_dice = 0;
                        //playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on);
                    } else {
                        enable_dice = 1;
                        //playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on);
                    } 
                }
                break;
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

/*
    printf("Snakes and ladders.\n");
    printf("Welcome!\n\n");

    printf("Game mode: \n");
    printf("1. practice.\n");
    printf("2. 2 players.\n");
    printf("3. against the computer. \n");
    scanf("%d", &game_mode);
    while(getchar() != '\n');

    saveGame(&name, player_position_one, player_position_two, current_turn, counter_dice_condition_one, counter_dice_condition_two, game_mode);
    printf("Game to load: ");
    scanf("%d", &game_load);
    loadGame(&name, game_mode, &player_position_one, &player_position_two, &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &game_mode);
*/