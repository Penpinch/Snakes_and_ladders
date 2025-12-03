#include "raylib.h"
#include "menu.h"

// Definimos los estados posibles de la aplicación

// Función auxiliar para dibujar texto centrado en un botón
void DrawTextCentered(const char* text, Rectangle btn, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize); //Se utiliza la función MeasureText() de Raylib. Esto mide cuántos píxeles ocupa el texto y permite colocarlo exactamente en el centro del botón, sin importar lo que escribas.
    int textX = btn.x + (btn.width - textWidth) / 2; //En lugar de coordenadas fijas (como 300), ahora se usa el ancho de la ventana 
    int textY = btn.y + (btn.height - fontSize) / 2; //para calcular el centro exacto: (screenWidth - buttonWidth) / 2.
    DrawText(text, textX, textY, fontSize, color);
}

// Función auxiliar para dibujar texto centrado en la pantalla 
void DrawTitleCentered(const char* text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize); //Se utiliza la función MeasureText() de Raylib. Esto mide cuántos píxeles ocupa el texto y permite colocarlo exactamente en el centro del botón, sin importar lo que escribas.
    int textX = (GetScreenWidth() - textWidth) / 2;
    DrawText(text, textX, y, fontSize, color);
}



Screen UpdateMenu(Screen actualScreen, int *game_mode) {
    // --- CONFIGURACIÓN DE TAMAÑOS ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    int btnWidth = 260;
    int btnHeight = 50;
    int spacing = 20;
    float btnX = (float)(screenWidth - btnWidth) / 2;
    float startY = 180;

    Vector2 mouse = GetMousePosition();

    Rectangle btnJugar   = { btnX, startY, btnWidth, btnHeight };
    Rectangle btnGuardar = { btnX, startY + (btnHeight + spacing), btnWidth, btnHeight };
    Rectangle btnCargar  = { btnX, startY + (btnHeight + spacing) * 2, btnWidth, btnHeight };

    Rectangle btnSub1 = { btnX, 150, btnWidth, btnHeight };
    Rectangle btnSub2 = { btnX, 150 + (btnHeight + spacing), btnWidth, btnHeight };
    Rectangle btnSub3 = { btnX, 150 + (btnHeight + spacing) * 2, btnWidth, btnHeight };
    Rectangle btnVolver = { btnX, 150 + (btnHeight + spacing) * 3 + 10, btnWidth, 40 };

    
    ClearBackground(RAYWHITE);
    

    switch (actualScreen) {

        // ---------------- MENÚ PRINCIPAL ----------------
        case MENU_PRINCIPAL:{
        
            DrawTitleCentered("SNAKES AND LADDERS", 80, 40, BLACK);

            // --- JUGAR ---
            if (CheckCollisionPointRec(mouse, btnJugar)) {
                DrawRectangleRec(btnJugar, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_JUEGO;
            } else{DrawRectangleRec(btnJugar, LIGHTGRAY);
            DrawTextCentered("JUGAR", btnJugar, 20, BLACK);
                }

            // --- GUARDAR ---
            if (CheckCollisionPointRec(mouse, btnGuardar)) {
                DrawRectangleRec(btnGuardar, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_GUARDAR;
            } else DrawRectangleRec(btnGuardar, LIGHTGRAY);
            DrawTextCentered("GUARDAR", btnGuardar, 20, BLACK);

            // --- CARGAR ---
            if (CheckCollisionPointRec(mouse, btnCargar)) {
                DrawRectangleRec(btnCargar, GRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_CARGA;
            } else DrawRectangleRec(btnCargar, LIGHTGRAY);
            DrawTextCentered("CARGAR", btnCargar, 20, BLACK);
        }break;
        

        // ---------------- MENU_JUEGO ----------------
        case MENU_JUEGO:{
        
            DrawTitleCentered("SELECCIONA DIFICULTAD", 80, 30, DARKBLUE);

            if (CheckCollisionPointRec(mouse, btnSub1)) {
                DrawRectangleRec(btnSub1, DARKGREEN);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    *game_mode = 1;
            } else DrawRectangleRec(btnSub1, GREEN);
            DrawTextCentered("UN JUGADOR", btnSub1, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnSub2)) {
                DrawRectangleRec(btnSub2, MAROON);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    *game_mode = 2;
            } else DrawRectangleRec(btnSub2, RED);
            DrawTextCentered("DOS JUGADORES", btnSub2, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnSub3)) {
                DrawRectangleRec(btnSub3, PURPLE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    *game_mode = 3;
            } else DrawRectangleRec(btnSub3, VIOLET);
            DrawTextCentered("CONTRA CPU", btnSub3, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnVolver)) {
                DrawRectangleRec(btnVolver, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_PRINCIPAL;
            } else DrawRectangleRec(btnVolver, GRAY);
            DrawTextCentered("VOLVER", btnVolver, 20, WHITE);
        }
        break;

        // ---------------- MENU_CARGA ----------------
        case MENU_CARGA:{
        
            DrawTitleCentered("CARGAR PARTIDA", 80, 30, DARKBLUE);

            if (CheckCollisionPointRec(mouse, btnSub1)) {
                DrawRectangleRec(btnSub1, BLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Cargando 1...");
            } else DrawRectangleRec(btnSub1, SKYBLUE);
            DrawTextCentered("PARTIDA 1", btnSub1, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnSub2)) {
                DrawRectangleRec(btnSub2, BLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Cargando 2...");
            } else DrawRectangleRec(btnSub2, SKYBLUE);
            DrawTextCentered("PARTIDA 2", btnSub2, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnSub3)) {
                DrawRectangleRec(btnSub3, BLUE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Cargando 3...");
            } else DrawRectangleRec(btnSub3, SKYBLUE);
            DrawTextCentered("PARTIDA 3", btnSub3, 20, WHITE);

            if (CheckCollisionPointRec(mouse, btnVolver)) {
                DrawRectangleRec(btnVolver, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_PRINCIPAL;
            } else DrawRectangleRec(btnVolver, GRAY);
            DrawTextCentered("VOLVER", btnVolver, 20, WHITE);
        }break;
        

        // ---------------- MENU_GUARDAR ----------------
        case MENU_GUARDAR:{
            DrawTitleCentered("GUARDAR PARTIDA", 80, 30, DARKGREEN);

            if (CheckCollisionPointRec(mouse, btnSub1)) {
                DrawRectangleRec(btnSub1, GOLD);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Guardando 1...");
            } else DrawRectangleRec(btnSub1, YELLOW);
            DrawTextCentered("SLOT VACIO 1", btnSub1, 20, BLACK);

            if (CheckCollisionPointRec(mouse, btnSub2)) {
                DrawRectangleRec(btnSub2, GOLD);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Guardando 2...");
            } else DrawRectangleRec(btnSub2, YELLOW);
            DrawTextCentered("SLOT VACIO 2", btnSub2, 20, BLACK);

            if (CheckCollisionPointRec(mouse, btnSub3)) {
                DrawRectangleRec(btnSub3, GOLD);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    TraceLog(LOG_INFO, "Guardando 3...");
            } else DrawRectangleRec(btnSub3, YELLOW);
            DrawTextCentered("SLOT VACIO 3", btnSub3, 20, BLACK);

            if (CheckCollisionPointRec(mouse, btnVolver)) {
                DrawRectangleRec(btnVolver, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    actualScreen = MENU_PRINCIPAL;
            } else DrawRectangleRec(btnVolver, GRAY);
            DrawTextCentered("VOLVER", btnVolver, 20, WHITE);
        }break;
        
    }

    return actualScreen;
}



