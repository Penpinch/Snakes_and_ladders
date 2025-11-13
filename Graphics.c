#include "raylib.h"
#include "grid.h"
#include <stdio.h>

/*
cd /d/proyecto/Snakes_and_ladders                                                                                                        
gcc Graphics.c -o prueba.exe -I /c/raylib/include -L /c/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole
./prueba.exe

{
    "files.associations": {
        "grid.h": "c",
        "stdio.h": "c"
    }
}
*/

void Grid_init(Grid *g, int cellsize) {
    g->rows = 10;
    g->columns = 10;
    g->cellsize = cellsize;
    for (int i = 0; i < g->rows; i++)
        for (int j = 0; j < g->columns; j++)
            g->grid[i][j] = 0;
}

int main(void){
    int cellsize = 60;
    Grid g;
    //Color darkBlue = {44, 44, 127, 255};
    Grid_init(&g, cellsize);//inicializa la estructura grid

    const int screenwidth = g.columns * g.cellsize;//ancho y alto de la pantalla, se calcula con la cantidad de filas/columans multiplicadas por el tamaño de cada una
    const int screenheight = g.rows * g.cellsize;
    char texto[50];

    InitWindow(screenwidth+150, screenheight+150, "Snakes And Ladderrs"); // ventana de inicializacion
    SetTargetFPS(60);

    while(!WindowShouldClose()){//mantiene la ventana abierta
        BeginDrawing();
        ClearBackground(RAYWHITE);
        

        for (int i = 0; i < g.columns; i++) {//dibuja las columnas
            int x = i * g.cellsize;
            DrawLine(x, 0, x, screenheight, BLACK);
}
        DrawLine(600, 0, 600, screenheight, BLACK);


        for (int j=0; j<=g.rows; j++){//dibuja las filas
            int y = j*g.cellsize;
            DrawLine(0,y,screenwidth,y, BLACK);
        }
        int counter = 1;
        for (int i = 0; i < g.rows; i++) {
            for (int j = 0; j < g.columns; j++) {
                int x = j * g.cellsize;
                int y = i * g.cellsize;
                sprintf(texto, "%d", counter);
                DrawText(texto, x + 20, screenheight-(i*g.cellsize) -40, 20, BLACK);
                counter++;
    }
}
        
        EndDrawing();
    }


    CloseWindow();//cierra la ventana 
    return 0;

}