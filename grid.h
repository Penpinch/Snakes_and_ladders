#ifndef GRID_H
#define GRID_H

#define ROWS 20
#define COLUMNS 10

typedef struct {
    int grid[ROWS][COLUMNS]; // 10 filas (x) y 10 columnas(y)
    int rows;
    int columns;
    int cellsize;
} Grid;

// Funciones para “constructor”
void Grid_init(Grid *g, int cellsize);

#endif