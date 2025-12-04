#ifndef MENU_H
#define MENU_h

#include "raylib.h"

struct PlayerName;

typedef enum{
    MENU_PRINCIPAL, 
    MENU_JUEGO,
    MENU_CARGA,
    MENU_GUARDAR    
}Screen; 

void DrawTextCentered(const char* text, Rectangle btn, int fontSize, Color color);

void DrawTitleCentered(const char* text, int y, int fontSize, Color color);

Screen UpdateMenu(
    Screen actualScreen, int *game_mode, int *save_option, int *load_game, int *player_position_one, int *player_position_two, 
    int *current_turn, int *counter_dice_condition_one, int *counter_dice_condition_two, int *dice_was_rolled, int *dice_value,
    int *writing_player_one, int *writing_player_two, struct PlayerName *name, int *names_done, int *new_game);

#endif