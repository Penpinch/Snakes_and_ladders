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

void showGrid(Grid *g, int cellsize, const int screenwidth, const int screenheight, char texto[]){
    for (int i = 0; i < g->columns; i++) {//Draw the columns
        int x = i * g->cellsize;
        DrawLine(x, 0, x, screenheight, BLACK);
    }
    DrawLine(600, 0, 600, screenheight, BLACK);

    for (int j=0; j<=g->rows; j++){//Draw the rows
        int y = j*g->cellsize;
        DrawLine(0,y,screenwidth,y, BLACK);
    }

    int counter = 1; 
    for (int i = 0; i < g->rows; i++) {//Draw the numbers
        for (int j = 0; j < g->columns; j++) {
            int x = j * g->cellsize;
            int y = i * g->cellsize;
            sprintf(texto, "%d", counter);
            DrawText(texto, x + 20, screenheight-(i*g->cellsize) -40, 20, BLACK);
            counter++;
        }
    }
}