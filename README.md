# Snakes and Ladders in C.

A school project implementing the classic game **Snakes and Ladders** in the **C** programming language, using **Raylib** for the graphical interface.

The game features multiple game modes and supports saving and loading progress.
## Features
- Graphical interface developed with Raylib
- Game logic implemented entirely in C
- Three game modes
- Multiplayer support
- Save and load game support

## Game Modes
- Single Player (individual mode, no CPU)
- Player vs Player
- Player vs CPU

## Requirements
- Operating system: Windows
- MSYS2
- GCC
- Raylib pre-installed

>This project assumes that Raylib is already correctly installed and configured on the system.

## Clone, Build and Run
To use this project locally:
```bash
git clone https://github.com/Penpinch/Snakes_and_ladders.git
cd Snakes_and_ladders
gcc snakesAndLadders.c logic.c menu.c -o finalver -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole
./finalver
```

## Game Saving
The game allows you to:
- Save your current game progress
- Load previously saved games from the menu

Saved files are stored locally.

## Technologies Used
- C programming language
- Raylib
- Git and GitHub

## Contributors
- @Penpinch
- @fabianelyorch
- @Ado-vAle
- @Dileny-lab
