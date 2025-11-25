#include "raylib.h"
#include "grid.h"
#include <stdio.h>

void Grid_init(Grid *g, int cellsize){//Initializa the matrix
    g->rows = 10;
    g->columns = 10;
    g->cellsize = cellsize;
    for (int i = 0; i < g->rows; i++)
        for (int j = 0; j < g->columns; j++)
            g->grid[i][j] = 0;
}

void showGrid(Grid *g, int cellsize, const int screenwidth, const int screenheight, char text[]){
    for (int i = 0; i < g->columns + 2; i++) {//Draw the columns
        int x = i * g->cellsize;
        DrawLine(x, 70, x, screenheight + 60, BLACK);
    }
    //DrawLine(660, 60, 660, screenheight + 60, BLACK);

    for (int j=0; j<=g->rows + 1; j++){//Draw the rows
        int y = j*g->cellsize;
        DrawLine(60,y,screenwidth + 60,y, BLACK);
    }

    int counter = 1; 
    for (int i = 0; i < g->rows; i++) {//Draw the numbers
        for (int j = 1; j < g->columns + 1; j++) {
            int x = j * g->cellsize;
            int y = i * g->cellsize;
            sprintf(text, "%d", counter);
            DrawText(text, x + 20, screenheight-(i*g->cellsize) + 20, 20, BLACK);
            counter++;
        }
    }
}

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