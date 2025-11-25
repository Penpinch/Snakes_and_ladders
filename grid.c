#include "raylib.h"
#include "grid.h"
#include <stdio.h>

void DrawDice(int dice_value, Texture2D dicetextures[]){
    if(dice_value < 1 || dice_value > 6){
        return;
    }
    Texture2D t = dicetextures[dice_value - 1];
    if(t.width <= 0 || t.height <= 0){
        return;
    }

    DrawTexture(dicetextures[dice_value - 1], 50, 750, WHITE);
}