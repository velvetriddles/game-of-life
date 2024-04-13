#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

void gameLoop(int grid[HEIGHT][WIDTH]);
void setupNcurses();
void finalizeNcurses();
void initializeGame(int grid[HEIGHT][WIDTH]);
void printGrid(int grid[HEIGHT][WIDTH], int offsetX, int offsetY);
void updateGrid(int grid[HEIGHT][WIDTH]);
void liveOrDead(int i, int j, int matrix[HEIGHT][WIDTH], int newMatrix[HEIGHT][WIDTH]);
void handleUserInput(int *gameRunning, int *speed);

int main() {
    int grid[HEIGHT][WIDTH] = {0};
    initializeGame(grid);
    if (freopen("/dev/tty", "r", stdin) != NULL) {
        setupNcurses();
        gameLoop(grid);
        finalizeNcurses();
    }
    return 0;
}

void setupNcurses() {
    initscr();
    cbreak();               // вроде бы ctrl + c,za
    noecho();               // -отображение клавиш
    curs_set(0);            // Скрыть курсор
    nodelay(stdscr, TRUE);  // Неблокирующий ввод
}

void finalizeNcurses() { endwin(); }

void gameLoop(int grid[HEIGHT][WIDTH]) {
    int gameRunning = 1;
    int speed = 100000;

    while (gameRunning) {
        int maxX, maxY, offsetX, offsetY;
        getmaxyx(stdscr, maxY, maxX);
        offsetX = (maxX - WIDTH) / 2;
        offsetY = (maxY - HEIGHT) / 2;

        printGrid(grid, offsetX, offsetY);
        updateGrid(grid);
        handleUserInput(&gameRunning, &speed);

        usleep(speed);
    }
}

void initializeGame(int grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

void printGrid(int grid[HEIGHT][WIDTH], int offsetX, int offsetY) {
    clear();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddch(offsetY + i, offsetX + j, grid[i][j] ? '*' : '.');
        }
    }
    refresh();
}

void updateGrid(int grid[HEIGHT][WIDTH]) {
    int newGrid[HEIGHT][WIDTH] = {0};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            liveOrDead(i, j, grid, newGrid);
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void liveOrDead(int i, int j, int matrix[HEIGHT][WIDTH], int newMatrix[HEIGHT][WIDTH]) {
    int neighbors = 0;
    // Подсчет живых соседей
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int row = (i + x + HEIGHT) % HEIGHT;
            int col = (j + y + WIDTH) % WIDTH;
            neighbors += matrix[row][col];
        }
    }
    // Правила "Жизни"
    if (matrix[i][j] == 1 && (neighbors < 2 || neighbors > 3))
        newMatrix[i][j] = 0;
    else if (matrix[i][j] == 0 && neighbors == 3)
        newMatrix[i][j] = 1;
    else
        newMatrix[i][j] = matrix[i][j];
}

void handleUserInput(int *gameRunning, int *speed) {
    int ch = getch();
    switch (ch) {
        case 'q':
            *gameRunning = 0;
            break;
        case '+':
            *speed = *speed > 20000 ? *speed - 20000 : 20000;
            break;
        case '-':
            *speed += 20000;
            break;
    }
}
// clang не забудь!!!