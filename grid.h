#ifndef GRID_H
#define GRID_H

typedef struct {
    int grid[20][10]; // 10 filas (x) y 10 columnas(y)
    int rows;
    int columns;
    int cellsize;
} Grid;

// Funciones para “constructor”
void Grid_init(Grid *g, int cellsize);

void showGrid(Grid *g, int cellsize, const int screenwidth, const int screenheight, char texto[]);

#endif 