# include "raylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "logic.h"
# include <string.h>
# include "grid.h" 
# include "menu.h"

//gcc snakesAndLadders.c logic.c grid.c menu.c -o finalver -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

void playerTurn(//Esta función tiene todo el apartado logico de los turnos, mover casilla, serpientes, escaleras, etc 
    int logic_board[], int board_size, int enable_dice, int *num_dice, 
    int *game_mode, int *player_position, int *counter_dice_condition, int *curren_turn, int *game_on, int *winner){

    *player_position = moveToken(*player_position, *num_dice);//Mueve la posición del jugador.
    printf("%d\n", *player_position);

    if(*player_position >= 100){//Verifica si el jugador gana.
        *player_position = 100;

        if(*game_mode == 1){
            *winner = 1;
            *game_on = 0;
            return;
        } else {
            *winner = *curren_turn % 2;
            if (*winner == 0){
                *winner = 2;
            }else{
                *winner = 1;
            }
            *game_on = 0;
            return;            
        }
    }

    *player_position = logic_board[*player_position];

    if(*num_dice == 6){//Verifica si se obtiene turno extra
        *curren_turn += 1;
        *counter_dice_condition += 1;
        (*counter_dice_condition < 2) ? *curren_turn -= 1 : (void)0;

        printf("contador valor: %d\n", *counter_dice_condition);
        if(*counter_dice_condition == 3){//Si obtiene 3 veces seguidas el número 6, regresa a la posición 1.
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

void drawToken(int *player_position, Color color){//Esta funcion dibuja las fichas.
    int indice = *player_position - 1;

    int fila = indice / 10;
    int invfila = 9 - fila;
    int col = indice % 10;
    int cell = 59;

    int x = 200 + col * cell;
    int y = 95 + invfila * cell;

    DrawCircle(x + cell/4 + 15, y + 3 * (cell/4), 14, color);
}

int main(){
    //Logic variables. 
    srand(time(NULL));

    int game_on = 1;//control
    int game_mode = 0, prev_game_mode = 0, game_load = 0, save_option = 0, new_game = 0, should_exit = 0;
    struct PlayerName name = {"", "Friend_computer"};

    int player_position_one = 1, counter_dice_condition_one = 0;   
    int player_position_two = 1, counter_dice_condition_two = 0;     
    int logic_board[101];
    int board_size = sizeof(logic_board) / sizeof(logic_board[0]);
    int current_turn = 5, dice_was_rolled = 0, dice_value = 0, enable_dice = 0;
    int winner = 0;
    int names_done = 0;

    initializeBoard(logic_board, board_size);//Inicializa el tablero lógico.
    cheekSpecialCell(logic_board);//Agrega las serpientes y escaleras en el tablero lógico.
    
    //Graphics variables.
    const int screenwidth = 1000;
    const int screenheight = 1000;

    char temporal_buffer_player_one[20] = {0};
    char temporal_buffer_player_two[20] = {0};
    char winner_output[40];
    int writing_player_one = 1;
    int writing_player_two = 0;

    InitWindow(screenwidth, screenheight, "Snakes And Ladders"); // Inicializa la ventana de Raylib.
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
    Screen actualScreen = MENU_PRINCIPAL; 
    while(!WindowShouldClose() && should_exit == 0){
        if(game_mode == 0){ 
            BeginDrawing();
                if (game_on == 1){
                    actualScreen = UpdateMenu(//Llama al menú.
                        actualScreen, &game_mode, &save_option, &game_load, &player_position_one, &player_position_two, 
                        &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &dice_was_rolled, &dice_value, 
                        &writing_player_one, &writing_player_two, &name, &names_done, &new_game, &should_exit);

                    if(IsKeyPressed(KEY_B)){
                        game_mode = prev_game_mode;
                    }
                }
            EndDrawing();

            if(game_load != 0 && game_on == 1){//Carga las partidas.
                loadGame(&name, &game_load, &player_position_one, &player_position_two, &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &game_mode, &names_done);
                game_load = 0;
                game_on = 1;
            }

            if(save_option != 0 && game_on == 1){//Guarda la partida.
                names_done = 2;
                saveGame(&name, save_option, player_position_one, player_position_two, current_turn, counter_dice_condition_one, counter_dice_condition_two, prev_game_mode, names_done);
                save_option = 0;
            }

            if(new_game == 1){//Devuelve las variables a su esatdo original para iniciar un nuevo juego.
                player_position_one = 1;
                counter_dice_condition_one = 0;
                player_position_two = 1;
                counter_dice_condition_two = 0;
                current_turn = 5;
                enable_dice = 0;
                dice_was_rolled = 0;
                dice_value = 0;
                winner = 0;
                names_done = 0;
                writing_player_one = 1;
                writing_player_two = 0;
                switch (game_mode){
                        case 1:
                            name.player_one_name[0] = '\0';
                            name.player_two_name[0] = '\0';
                            break;
                        case 2:
                            name.player_one_name[0] = '\0';
                            name.player_two_name[0] = '\0';
                            break;
                            
                        case 3:
                            strcpy(name.player_one_name, "");
                            strcpy(name.player_two_name, "Friend_computer");
                            break;
                }
                new_game = 0;
            }

        } else if(game_mode != 0){
            if(names_done == 0){//Captura de nombres.
                int captura = capturePlayerName(temporal_buffer_player_one, temporal_buffer_player_two, &writing_player_one, &writing_player_two, game_mode);

                BeginDrawing();
                ClearBackground(BEIGE);
                if(writing_player_one){
                    DrawText("Player 1 name: ", 50, 50, 45, BLACK);
                    DrawText(temporal_buffer_player_one, 50, 100, 35, RED);
                }
                if(writing_player_two){
                    DrawText("Player 2 name: ", 50, 50, 45, BLACK);
                    DrawText(temporal_buffer_player_two, 50, 100, 35, DARKBLUE);
                }
                EndDrawing();
                if(captura == 1){
                    names_done = 1;
                }
                continue;
            }

            if(names_done == 1){//Establece el nombre del jugador 2 para el modo de 2 jugadores.
                names_done = 2;
                char *p2 = (game_mode == 2) ? temporal_buffer_player_two : "";
                setName(&name, game_mode, temporal_buffer_player_one, p2);
            }

            if(game_on == 1 && names_done == 2){//Detecta si se presiona la barra espaciadora para tirar el dado.
                if(IsKeyPressed(KEY_SPACE) && enable_dice == 0 && dice_was_rolled == 0){
                    dice_value = rollDice();
                    dice_was_rolled = 1;
                    printf("%d -> dice value = %d\n",current_turn ,dice_value);
                    fflush(stdout);
                } else if(enable_dice == 1 && dice_was_rolled == 0){
                    dice_value = rollDice();
                    dice_was_rolled = 1;
                    printf(" computer -> dice value = %d\n", dice_value);
                    fflush(stdout);
                }
            }

            BeginDrawing();
            if(game_on == 1){//Secuencia del juego.
                ClearBackground(BLUE);
                DrawTexture(grid_image, 0, 0, WHITE);//Tablero en el fondo.
                DrawText("Press space key to roll the dice.", (1000 - MeasureText("Press space key to roll the dice.", 30)) / 2, 40, 30, BLACK);
                DrawDice(dice_value, dicetextures); //Dibuja el dado.
                drawToken(&player_position_one, RED);//Dibuja la fihca del jugador 1.
                drawToken(&player_position_two, BLUE);//Dibuja la fihca del jugador 2.
                
                DrawText("Don't let it get to 3!", 730, 760, 25, BLACK);
                char showcdc[2];
                sprintf(showcdc, "%d", counter_dice_condition_one);
                DrawText(showcdc, 820, 800, 25, RED);

                DrawText(name.player_one_name, 275, 760, 35, RED);//Dibuja los nombres.
                if(game_mode != 1){
                    DrawText(name.player_two_name, 275, 860, 35, BLUE);
                    sprintf(showcdc, "%d", counter_dice_condition_two);
                    DrawText(showcdc, 920, 800, 25, BLUE);
                }

                DrawText("'s' to exit.", 600, 950, 25, BLACK);
                DrawText("'b' to go back.", 800, 950, 25, BLACK);

                switch(game_mode){//Lógica de los 3 modos de juego.
                    case 1://Modo en solitario.
                        if(dice_was_rolled == 1){
                            playerTurn(logic_board, board_size, enable_dice, &dice_value, &game_mode, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                            dice_was_rolled = 0;
                        }
                        break;
                    case 2://Modo de 2 jugadores.
                        if(dice_was_rolled == 1){
                            if(current_turn % 2 == 0){
                                playerTurn(logic_board, board_size, enable_dice, &dice_value, &game_mode, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on, &winner);
                            } else {
                                playerTurn(logic_board, board_size, enable_dice, &dice_value, &game_mode, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                            }
                            dice_was_rolled = 0;
                        }
                        break;
                    case 3://Modo contra la computadora.
                        if(dice_was_rolled == 1){
                            if(current_turn % 2 == 0){
                                playerTurn(logic_board, board_size, enable_dice, &dice_value, &game_mode, &player_position_two, &counter_dice_condition_two, &current_turn, &game_on, &winner);
                            } else {
                                playerTurn(logic_board, board_size, enable_dice, &dice_value, &game_mode, &player_position_one, &counter_dice_condition_one, &current_turn, &game_on, &winner);
                            }
                            dice_was_rolled = 0;

                            //(current_turn % 2 != 0) ? WaitTime(2.0) : (void)0;
                            enable_dice = (current_turn % 2 == 0) ? 1 : 0;
                        }
                        break;
                    }

            if(IsKeyPressed(KEY_S)){
                ClearBackground(BEIGE);
                prev_game_mode = game_mode;
                game_on = 1;
                game_mode = 0;
                actualScreen = UpdateMenu(//Llama al menú de guardado.
                    MENU_GUARDAR, &game_mode, &save_option, &game_load, &player_position_one, &player_position_two, 
                    &current_turn, &counter_dice_condition_one, &counter_dice_condition_two, &dice_was_rolled, &dice_value, 
                    &writing_player_one, &writing_player_two, &name, &names_done, &new_game, &should_exit);
            }

            } else if(game_on == 0 && player_position_one >= 100 || player_position_two >= 100){//Pantalla de ganador.
                ClearBackground(LIGHTGRAY);  
                
                DrawText("Press w to exit.", (1000 - MeasureText("Press w to exit.", 30)) / 2, 950, 30, BLACK);

                int text_width = MeasureText(winner_output, 50);
                if(winner == 2){
                    sprintf(winner_output, "Player %s wins!", name.player_two_name);
                    DrawText(winner_output, (1000 - text_width) / 2, (1000 - 50) / 2, 50, BLUE);
                } else {
                    sprintf(winner_output, "Player %s wins!", name.player_one_name);
                    DrawText(winner_output, (1000 - text_width) / 2, (1000 - 50) / 2, 50, RED);
                }

                if(IsKeyPressed(KEY_W)){
                    prev_game_mode = game_mode;
                    game_on = 1;
                    game_mode = 0;
                    winner = 0;
                }
            }
            EndDrawing();
        } 
    }
    CloseWindow();
    return 0;
}