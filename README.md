# Game of Life in C using ncurses

This is an implementation of Conway's Game of Life in C using the ncurses library for display.

## Description

The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. This program visualizes the Game of Life in the terminal using the ncurses library for displaying the grid and handling user input.

## Features

- Display the current state of the cells on the screen.
- Update the state of the cells according to the rules of the Game of Life.
- Control the update speed.
- Ability to terminate the program.

## Rules

1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

## Requirements

- C compiler (e.g., gcc)
- ncurses library (installable via package manager, e.g., `sudo apt-get install libncurses5-dev libncursesw5-dev`)

## Installation and Running

1. Clone the repository or download the source code.
2. Navigate to the directory with the source code.
3. Compile the project using gcc:

    ```sh
    gcc -o game_of_life game_of_life.c -lncurses
    ```

4. Run the compiled program:

    ```sh
    ./game_of_life
    ```

## Input Data

The program expects the initial configuration of the cells from the standard input. Cells are input as 0s and 1s, where 0 is a dead cell and 1 is a live cell.

Example input:
```
0 1 0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 1 0 0
1 1 1 0 0 0 0 0 1 1
...
```


## Controls

- `q` — Quit the program.
- `+` — Increase the update speed.
- `-` — Decrease the update speed.

## Example Usage

```sh
./game_of_life < initial_grid.txt
