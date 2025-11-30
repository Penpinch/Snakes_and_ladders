#include "raylib.h"

// Definimos los estados posibles de la aplicación
typedef enum { 
    MENU_PRINCIPAL, 
    MENU_JUEGO,
    MENU_CARGA,
    MENU_GUARDAR 
} Pantalla;

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

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SNAKES AND LADDERS");
    SetTargetFPS(60);

    // Variable para saber en qué pantalla estamos
    Pantalla pantallaActual = MENU_PRINCIPAL;

    // --- CONFIGURACIÓN DE TAMAÑOS ---
    int btnWidth = 260;  // Un ancho estándar para que quepa bien el texto
    int btnHeight = 50;
    int spacing = 20;    // Espacio entre botones
    
    // Calculamos la posición X para que los botones estén centrados horizontalmente
    float btnX = (float)(screenWidth - btnWidth) / 2;

    // Definimos las posiciones Y base para los botones
    float startY = 180; 

    //bucle del juego
    while (!WindowShouldClose()) {
        //sigue la pocicion del mouse cada frame
        Vector2 mouse = GetMousePosition();

        // Actualizamos los rectángulos en cada frame o definimos sus posiciones base
        // Botones Menú Principal
        Rectangle btnJugar   = { btnX, startY, (float)btnWidth, (float)btnHeight };
        Rectangle btnGuardar = { btnX, startY + (btnHeight + spacing), (float)btnWidth, (float)btnHeight };
        Rectangle btnCargar  = { btnX, startY + (btnHeight + spacing) * 2, (float)btnWidth, (float)btnHeight };

        // Botones Submenús (Misma lógica, pero quizás queramos 4 botones contando 'Volver')
        Rectangle btnSub1 = { btnX, 150, (float)btnWidth, (float)btnHeight };
        Rectangle btnSub2 = { btnX, 150 + (float)(btnHeight + spacing), (float)btnWidth, (float)btnHeight };
        Rectangle btnSub3 = { btnX, 150 + (float)(btnHeight + spacing) * 2, (float)btnWidth, (float)btnHeight };
        Rectangle btnVolver = { btnX, 150 + (float)(btnHeight + spacing) * 3 + 10, (float)btnWidth, 40 };

        //inicia a dibujar
        BeginDrawing();
        //limpia la pantalla cada frama
        ClearBackground(RAYWHITE);

        switch (pantallaActual) {
            
            // ---------------- CASO 1: MENÚ PRINCIPAL ----------------
            case MENU_PRINCIPAL:
            {
                DrawTitleCentered("SNAKES AND LADDERS", 80, 40, BLACK);

                // --- Botón JUGAR ---
                if (CheckCollisionPointRec(mouse, btnJugar)) {
                    DrawRectangleRec(btnJugar, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_JUEGO;
                } else DrawRectangleRec(btnJugar, LIGHTGRAY);
                DrawTextCentered("JUGAR", btnJugar, 20, BLACK);

                // --- Botón GUARDAR ---
                if (CheckCollisionPointRec(mouse, btnGuardar)) {
                    DrawRectangleRec(btnGuardar, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_GUARDAR;
                } else DrawRectangleRec(btnGuardar, LIGHTGRAY);
                DrawTextCentered("GUARDAR", btnGuardar, 20, BLACK);

                // --- Botón CARGAR ---
                if (CheckCollisionPointRec(mouse, btnCargar)) {
                    DrawRectangleRec(btnCargar, GRAY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_CARGA;
                } else DrawRectangleRec(btnCargar, LIGHTGRAY);
                DrawTextCentered("CARGAR", btnCargar, 20, BLACK);
            } break;

            // ---------------- CASO 2: MODO DE JUEGO ----------------
            case MENU_JUEGO:
            {
                DrawTitleCentered("SELECCIONA DIFICULTAD", 80, 30, DARKBLUE);

                // Opción 1
                if (CheckCollisionPointRec(mouse, btnSub1)) {
                    DrawRectangleRec(btnSub1, DARKGREEN);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "UN JUGADOR");
                } else DrawRectangleRec(btnSub1, GREEN);
                DrawTextCentered("UN JUGADOR", btnSub1, 20, WHITE);

                // Opción 2
                if (CheckCollisionPointRec(mouse, btnSub2)) {
                    DrawRectangleRec(btnSub2, MAROON);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "DOS JUGADORES");
                } else DrawRectangleRec(btnSub2, RED);
                DrawTextCentered("DOS JUGADORES", btnSub2, 20, WHITE);

                // Opción 3
                if (CheckCollisionPointRec(mouse, btnSub3)) {
                    DrawRectangleRec(btnSub3, PURPLE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "CONTRA LA CPU");
                } else DrawRectangleRec(btnSub3, VIOLET);
                DrawTextCentered("CONTRA LA CPU", btnSub3, 20, WHITE);

                // Volver
                if (CheckCollisionPointRec(mouse, btnVolver)) {
                    DrawRectangleRec(btnVolver, BLACK);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_PRINCIPAL;
                } else DrawRectangleRec(btnVolver, GRAY);
                DrawTextCentered("VOLVER", btnVolver, 20, WHITE);

            } break;

            // ---------------- CASO 3: CARGAR PARTIDA ----------------
            case MENU_CARGA:
            {
                DrawTitleCentered("CARGAR PARTIDA", 80, 30, DARKBLUE);

                if (CheckCollisionPointRec(mouse, btnSub1)) {
                    DrawRectangleRec(btnSub1, BLUE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Cargando 1...");
                } else DrawRectangleRec(btnSub1, SKYBLUE);
                DrawTextCentered("PARTIDA 1", btnSub1, 20, WHITE);

                if (CheckCollisionPointRec(mouse, btnSub2)) {
                    DrawRectangleRec(btnSub2, BLUE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Cargando 2...");
                } else DrawRectangleRec(btnSub2, SKYBLUE);
                DrawTextCentered("PARTIDA 2", btnSub2, 20, WHITE);

                if (CheckCollisionPointRec(mouse, btnSub3)) {
                    DrawRectangleRec(btnSub3, BLUE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Cargando 3...");
                } else DrawRectangleRec(btnSub3, SKYBLUE);
                DrawTextCentered("PARTIDA 3", btnSub3, 20, WHITE);

                if (CheckCollisionPointRec(mouse, btnVolver)) {
                    DrawRectangleRec(btnVolver, BLACK);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_PRINCIPAL;
                } else DrawRectangleRec(btnVolver, GRAY);
                DrawTextCentered("VOLVER", btnVolver, 20, WHITE);

            } break;

            // ---------------- CASO 4: GUARDAR PARTIDA ----------------
            case MENU_GUARDAR:
            {
                DrawTitleCentered("GUARDAR PARTIDA", 80, 30, DARKGREEN);

                if (CheckCollisionPointRec(mouse, btnSub1)) {
                    DrawRectangleRec(btnSub1, GOLD);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Guardando 1...");
                } else DrawRectangleRec(btnSub1, YELLOW);
                DrawTextCentered("SLOT VACIO 1", btnSub1, 20, BLACK);

                if (CheckCollisionPointRec(mouse, btnSub2)) {
                    DrawRectangleRec(btnSub2, GOLD);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Guardando 2...");
                } else DrawRectangleRec(btnSub2, YELLOW);
                DrawTextCentered("SLOT VACIO 2", btnSub2, 20, BLACK);

                if (CheckCollisionPointRec(mouse, btnSub3)) {
                    DrawRectangleRec(btnSub3, GOLD);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) TraceLog(LOG_INFO, "Guardando 3...");
                } else DrawRectangleRec(btnSub3, YELLOW);
                DrawTextCentered("SLOT VACIO 3", btnSub3, 20, BLACK);

                if (CheckCollisionPointRec(mouse, btnVolver)) {
                    DrawRectangleRec(btnVolver, BLACK);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pantallaActual = MENU_PRINCIPAL;
                } else DrawRectangleRec(btnVolver, GRAY);
                DrawTextCentered("VOLVER", btnVolver, 20, WHITE);

            } break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}