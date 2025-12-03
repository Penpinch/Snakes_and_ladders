#ifndef MENU_H
#define MENU_h
#include "raylib.h"

typedef enum{
    MENU_PRINCIPAL, 
    MENU_JUEGO,
    MENU_CARGA,
    MENU_GUARDAR    
}Screen; 

void DrawTextCentered(const char* text, Rectangle btn, int fontSize, Color color);

void DrawTitleCentered(const char* text, int y, int fontSize, Color color);

Screen UpdateMenu(Screen actualScreen, int *game_mode);

#endif