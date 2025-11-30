# include "raylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "logic.h"
# include <string.h>
# include "grid.h" 

//gcc snakesAndLadders.c logic.c grid.c -o q -lraylib -lopengl32 -lgdi32 -mconsole

void playerTurn(//Esta función tiene todo el apartado logico de los turnos, mover casilla, serpientes, escaleras, etc 
    int logic_board[], int board_size, int enable_dice, int *num_dice, 
    int *player_position, int *counter_dice_condition, int *curren_turn, int *game_on, int *winner){

    *player_position = moveToken(*player_position, *num_dice);
    printf("%d\n", *player_position);

    if(*player_position >= 100){
        *player_position = 100;
        *winner = *curren_turn % 2;
        if (*winner == 0){
            *winner = 2;
        }else{
            *winner = 1;
        }
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
}

int capturePlayerName(//Esta funcion captura el nombre del los jugadores.
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
    //Logic variables. DO NOT TOUCH.
    srand(time(NULL));

    int game_on = 1;//control
    int game_mode = 3, enable_dice = 1, game_load, save_option; //pruebas
    struct PlayerName name = {"", "Computer friend"};

    int player_position_one = 1, counter_dice_condition_one = 0;   
    int player_position_two = 1, counter_dice_condition_two = 0;     
    int logic_board[101];
    int board_size = sizeof(logic_board) / sizeof(logic_board[0]);
    int current_turn = 5, dice_was_rolled = 0, dice_value = 0;
    int winner;

    initializeBoard(logic_board, board_size);//Inicializa el tablero lógico.
    cheekSpecialCell(logic_board);//Re-asigna las serpientes y escaleras en el tablero lógico.
    
    //Graphics variables. DO NOT TOUCH
    const int screenwidth = 1000;
    const int screenheight = 1000;

    char temporal_buffer_player_one[20] = {0};
    char temporal_buffer_player_two[20] = {0};
    char winner_output[40];
    int writing_player_one = 1;
    int writing_player_two = 0;
    int names_done = 0;

    InitWindow(screenwidth, screenheight, "Snakes And Ladders"); // ventana de inicialización de Raylib.
    SetTargetFPS(60);//Fotogramas por segundo.
    Texture2D grid_image;
    grid_image = LoadTexture("Grid_image.png");
    Texture2D dicetextures[6]; //Inicializa las imagenes del dado.
    dicetextures[0] = LoadTexture("Dice_faces/DiceFace1.png");//Carga las imagenes del dado.
    dicetextures[1] = LoadTexture("Dice_faces/DiceFace2.png");
    dicetextures[2] = LoadTexture("Dice_faces/DiceFace3.png");
    dicetextures[3] = LoadTexture("Dice_faces/DiceFace4.png");
    dicetextures[4] = LoadTexture("Dice_faces/DiceFace5.png");
    dicetextures[5] = LoadTexture("Dice_faces/DiceFace6.png");

    temporal_buffer_player_one[0] = '\0';
    temporal_buffer_player_two[0] = '\0';
    while(!WindowShouldClose()){

        if(names_done == 0){//Captura de nombres.
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

        if(names_done == 1){//Si aún no los captura, lo hace.
            names_done = 2;
            const char *p2 = (game_mode == 2) ? temporal_buffer_player_two : "";
            setName(&name, game_mode, temporal_buffer_player_one, p2);
        }

        if(game_on == 1 && names_done == 2){//Detecta si se presiona la barra espaciadora para tirar el dado.
            if(IsKeyPressed(KEY_SPACE) && enable_dice == 0 && dice_was_rolled == 0){
                dice_value = rollDice();
                dice_was_rolled = 1;
                printf("sapce presed -> dice value = %d\n", dice_value);
                fflush(stdout);
            } else if(enable_dice == 1 && dice_was_rolled == 0){
                dice_value = rollDice();
                dice_was_rolled = 1;
                printf(" computer -> dice value = %d\n", dice_value);
                fflush(stdout);
            }
        }

        BeginDrawing();

        if(game_on == 1){
            ClearBackground(BLUE);
            DrawTexture(grid_image, 0, 0, WHITE);
            DrawText("Press space key to roll the dice.", 250, 40, 30, BLACK);
            DrawDice(dice_value, dicetextures); //dibuja el dado
            DrawText(name.player_one_name, 300, 760, 30, BLACK); 
            if(game_mode != 1){
                DrawText(name.player_two_name, 300, 860, 30, BLACK);
            }

            switch(game_mode){//Tres modos de jjuego.
                case 1:
                    if(dice_was_rolled == 1){
                        playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                        dice_was_rolled = 0;
                    }
                    break;
                case 2:
                    if(dice_was_rolled == 1){
                        if(current_turn % 2 == 0){
                            playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on, &winner);
                        } else {
                            playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                        }
                        dice_was_rolled = 0;
                    }
                    break;
                case 3:
                    if(dice_was_rolled == 1){
                        if(current_turn % 2 == 0){
                            enable_dice = 0;
                            playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on, &winner);
                        } else {
                            enable_dice = 1;
                            playerTurn(logic_board, board_size, enable_dice, &dice_value, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                        }
                        dice_was_rolled = 0;
                    }
                    break;
            }
        } else if(game_on == 0){
            ClearBackground(LIGHTGRAY);  
            DrawText("Press w to exit.", 500, 200, 50, BLUE);

            if(winner == 2){
                sprintf(winner_output, "Player %s wins!", name.player_two_name);
                DrawText(winner_output, 300, 500, 50, BLUE);
            } else {
                sprintf(winner_output, "Player %s wins!", name.player_one_name);
                DrawText(winner_output, 300, 500, 50, BLUE);
            }

            if(IsKeyPressed(KEY_W)){
                break;
            }
        }

        EndDrawing();

        //Agregar botones para usar esto
/*        BeginDrawing();//Recibe donde guardar la partida.
            ClearBackground(PURPLE);
            DrawText("Where to save? ", 500, 500, 30, BLACK);
            DrawText("1. Save 1", 500, 550, 30, BLACK);
            DrawText("2. Save 2", 500, 600, 30, BLACK);
            DrawText("3. Save 3", 500, 650, 30, BLACK);
            DrawText("4. Save 4", 500, 700, 30, BLACK);
            
            if(IsKeyPressed(KEY_ONE)){
                save_option = 1;
                break;
            } else if(IsKeyPressed(KEY_TWO)){
                save_option = 2;
                break;
            } else if(IsKeyPressed(KEY_THREE)){
                save_option = 3;
                break;
            } else if(IsKeyPressed(KEY_FOUR)){
                save_option = 4;
                break;
            }
        EndDrawing();
        
        //Esto va en el menu q va a hacer Ale
        BeginDrawing();//Recibe que partida cargar.
            ClearBackground(PURPLE);
            DrawText("Game to load? ", 500, 500, 30, BLACK);
            DrawText("1. Load game 1", 500, 550, 30, BLACK);
            DrawText("2. Load game 2", 500, 600, 30, BLACK);
            DrawText("3. Load game 3", 500, 650, 30, BLACK);
            DrawText("4. Load game 4", 500, 700, 30, BLACK);
            if(IsKeyPressed(KEY_ONE)){
                game_load = 1;
                break;
            } else if(IsKeyPressed(KEY_TWO)){
                game_load = 2;
                break;
            } else if(IsKeyPressed(KEY_THREE)){
                game_load = 3;
                break;
            } else if(IsKeyPressed(KEY_FOUR)){
                game_load = 4;
                break;
            }
        EndDrawing();
    */
    }
    //saveGame(&name, save_option, player_position_one, player_position_two, current_turn, counter_dice_condition_one, counter_dice_condition_two, game_mode);
    //loadGame(&name, game_load, &player_position_one, &player_position_two, &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &game_mode);

    CloseWindow();
    return 0;
}