#include "raylib.h"
#include "menu.h"
#include "logic.h"
#include <stdio.h>

// Definimos los estados posibles de la aplicación

// Función auxiliar para dibujar texto centrado en un botón
void DrawTextCentered(const char* text, Rectangle btn, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize); //Se utiliza la función MeasureText() de Raylib. Esto mide cuántos píxeles ocupa el texto y permite colocarlo exactamente en el centro del botón, sin importar lo que escribas.
    int textX = btn.x + (btn.width - textWidth) / 2; //En lugar de coordenadas fijas, ahora se usa el ancho de la ventana 
    int textY = btn.y + (btn.height - fontSize) / 2; //para calcular el centro exacto: (screenWidth - buttonWidth) / 2.
    DrawText(text, textX, textY, fontSize, color);
}

// Función auxiliar para dibujar texto centrado en la pantalla 
void DrawTitleCentered(const char* text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize); //Se utiliza la función MeasureText() de Raylib. Esto mide cuántos píxeles ocupa el texto y permite colocarlo exactamente en el centro del botón, sin importar lo que escribas.
    int textX = (GetScreenWidth() - textWidth) / 2;
    DrawText(text, textX, y, fontSize, color);
}

Screen UpdateMenu(
    Screen actualScreen, int *game_mode, int *save_option, int *load_game, int *player_position_one, int *player_position_two, 
    int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *dice_was_rolled, int *dice_value, 
    int *writing_player_one, int *writing_player_two, struct PlayerName *name, int *names_done, int *new_game, int *should_exit){
    // --- CONFIGURACIÓN DE TAMAÑOS ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    int btnWidth = 260;
    int btnHeight = 50;
    int spacing = 20;
    float btnX = (float)(screenWidth - btnWidth) / 2;
    float startY = 180;

    Vector2 mouse = GetMousePosition();

    Rectangle btnJugar   = {btnX, startY, btnWidth, btnHeight};
    Rectangle btnGuardar = {btnX, startY + (btnHeight + spacing), btnWidth, btnHeight};
    Rectangle btnCargar  = {btnX, startY + (btnHeight + spacing) * 2, btnWidth, btnHeight};
    Rectangle btnSalir = {btnX, startY + (btnHeight + spacing) * 3, btnWidth, btnHeight};

    Rectangle btnSub1 = {btnX, 150, btnWidth, btnHeight};
    Rectangle btnSub2 = {btnX, 150 + (btnHeight + spacing), btnWidth, btnHeight};
    Rectangle btnSub3 = {btnX, 150 + (btnHeight + spacing) * 2, btnWidth, btnHeight};
    Rectangle btnVolver = {btnX, 150 + (btnHeight + spacing) * 3 + 10, btnWidth, 40};

    ClearBackground(RAYWHITE);

    switch(actualScreen){

        // ---------------- MENÚ PRINCIPAL ----------------
        case MENU_PRINCIPAL:{
            ClearBackground(BEIGE);
            DrawTitleCentered("SNAKES AND LADDERS", 80, 40, BLACK);
            float centerX_menu_princ = (GetScreenWidth() - btnJugar.width) / 2;
            btnJugar.x = centerX_menu_princ;
            btnGuardar.x = centerX_menu_princ;
            btnCargar.x = centerX_menu_princ;
            btnSalir.x = centerX_menu_princ;
            btnVolver.x = centerX_menu_princ;

            // --- JUGAR ---
            if (CheckCollisionPointRec(mouse, btnJugar)){
                DrawRectangleRec(btnJugar, GRAY);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_JUEGO;
                }
            } else {DrawRectangleRec(btnJugar, LIGHTGRAY);
                DrawTextCentered("JUGAR", btnJugar, 20, BLACK);
            }

            // --- GUARDAR ---
            if(CheckCollisionPointRec(mouse, btnGuardar)) {
                DrawRectangleRec(btnGuardar, GRAY);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_GUARDAR;
                }
            } else {DrawRectangleRec(btnGuardar, LIGHTGRAY);
                DrawTextCentered("GUARDAR", btnGuardar, 20, BLACK);
            }

            // --- CARGAR ---
            if(CheckCollisionPointRec(mouse, btnCargar)){
                DrawRectangleRec(btnCargar, GRAY);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_CARGA;
                }
            } else {DrawRectangleRec(btnCargar, LIGHTGRAY);
                DrawTextCentered("CARGAR", btnCargar, 20, BLACK);
            }

            // --- SALIR ---
            if(CheckCollisionPointRec(mouse, btnSalir)){
                DrawRectangleRec(btnSalir, GRAY);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *should_exit = 1;
                }
            } else {DrawRectangleRec(btnSalir, LIGHTGRAY);
                DrawTextCentered("SALIR", btnSalir, 20, BLACK);
            }

        }break;

        // ---------------- MENU_JUEGO ----------------
        case MENU_JUEGO:{
            ClearBackground(BEIGE);
            DrawTitleCentered("SELECCIONA MODO DE JUEGO", 80, 30, DARKBLUE);
            float centerX = (GetScreenWidth() - btnSub1.width) / 2;
            btnSub1.x = centerX;
            btnSub2.x = centerX;
            btnSub3.x = centerX;
            btnVolver.x = centerX;

            if(CheckCollisionPointRec(mouse, btnSub1)){
                DrawRectangleRec(btnSub1, DARKGREEN);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *new_game = 1;
                    *game_mode = 1;
                }
            } else {DrawRectangleRec(btnSub1, GREEN);
                DrawTextCentered("UN JUGADOR", btnSub1, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnSub2)){
                DrawRectangleRec(btnSub2, MAROON);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *new_game = 1;
                    *game_mode = 2;
                }
            } else {DrawRectangleRec(btnSub2, RED);
                DrawTextCentered("DOS JUGADORES", btnSub2, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnSub3)){
                DrawRectangleRec(btnSub3, PURPLE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *new_game = 1;
                    *game_mode = 3;
                }
            } else {DrawRectangleRec(btnSub3, VIOLET);
                DrawTextCentered("CONTRA CPU", btnSub3, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnVolver)){
                DrawRectangleRec(btnVolver, BLACK);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_PRINCIPAL;
                }
            } else {DrawRectangleRec(btnVolver, GRAY);
                DrawTextCentered("VOLVER", btnVolver, 20, WHITE);
            }
        }
        break;

        // ---------------- MENU_CARGA ----------------
        case MENU_CARGA:{
            ClearBackground(BEIGE);
            DrawTitleCentered("CARGAR PARTIDA", 80, 30, DARKBLUE);
            float btnX = (GetScreenWidth() - btnWidth) / 2;
            Rectangle btnLoad1 = {btnX, 150, btnWidth, btnHeight};
            Rectangle btnLoad2 = {btnX, 150 + (btnHeight + spacing), btnWidth, btnHeight};
            Rectangle btnLoad3 = {btnX, 150 + (btnHeight + spacing) * 2, btnWidth, btnHeight};
            Rectangle btnLoadBack = {btnX, 150 + (btnHeight + spacing) * 3 + 10, btnWidth, 40};

            if(CheckCollisionPointRec(mouse, btnLoad1)){
                DrawRectangleRec(btnLoad1, BLUE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *load_game = 1;
                }
            } else {DrawRectangleRec(btnLoad1, SKYBLUE);
                DrawTextCentered("PARTIDA 1", btnLoad1, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnLoad2)){
                DrawRectangleRec(btnLoad2, BLUE);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *load_game = 2;
                }
            } else {DrawRectangleRec(btnLoad2, SKYBLUE);
                DrawTextCentered("PARTIDA 2", btnLoad2, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnLoad3)){
                DrawRectangleRec(btnLoad3, BLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *load_game = 3;
                }
            } else {DrawRectangleRec(btnLoad3, SKYBLUE);
                DrawTextCentered("PARTIDA 3", btnLoad3, 20, WHITE);
            }

            if(CheckCollisionPointRec(mouse, btnLoadBack)){
                DrawRectangleRec(btnLoadBack, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_PRINCIPAL;
                }
            } else {DrawRectangleRec(btnLoadBack, GRAY);
                DrawTextCentered("VOLVER", btnLoadBack, 20, WHITE);
            }
        }break;

        // ---------------- MENU_GUARDAR ----------------
        case MENU_GUARDAR:{
            ClearBackground(BEIGE);
            DrawTitleCentered("GUARDAR PARTIDA", 80, 30, DARKGREEN);
            float centerX_menu_guar = (GetScreenWidth() - btnSub1.width) / 2;
            btnSub1.x = centerX_menu_guar;
            btnSub2.x = centerX_menu_guar;
            btnSub3.x = centerX_menu_guar;
            btnVolver.x = centerX_menu_guar;

            if(CheckCollisionPointRec(mouse, btnSub1)){
                DrawRectangleRec(btnSub1, GOLD);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *save_option = 1;
                    printf("%d", save_option);
                }
            } else {DrawRectangleRec(btnSub1, YELLOW);
                DrawTextCentered("SLOT VACIO 1", btnSub1, 20, BLACK);
            }

            if(CheckCollisionPointRec(mouse, btnSub2)){
                DrawRectangleRec(btnSub2, GOLD);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *save_option = 2;
                    printf("%d", save_option);
                }
            } else {DrawRectangleRec(btnSub2, YELLOW);
                DrawTextCentered("SLOT VACIO 2", btnSub2, 20, BLACK);
            }

            if(CheckCollisionPointRec(mouse, btnSub3)){
                DrawRectangleRec(btnSub3, GOLD);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    *save_option = 3;
                    printf("%d", save_option);
                }
            } else {DrawRectangleRec(btnSub3, YELLOW);
                DrawTextCentered("SLOT VACIO 3", btnSub3, 20, BLACK);
            }

            if(CheckCollisionPointRec(mouse, btnVolver)){
                DrawRectangleRec(btnVolver, BLACK);
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    actualScreen = MENU_PRINCIPAL;
                }
            } else {DrawRectangleRec(btnVolver, GRAY);
                DrawTextCentered("VOLVER", btnVolver, 20, WHITE);
            }
        }break;
    }
    return actualScreen;
}



