#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define CLEAR "cls"

using namespace std;

enum Direction { STOP = 0, UP, DOWN, RIGHT, LEFT };

void showIntro() {
    cout << "\033[31m"; // Set color to Red
    cout << "Welcome to Snake Game\n";
    cout << "\033[37m\n"; // Reset color to white

    cout << "\033[36m"; // Set color to Cyan
    cout << "Game Controls:\n";
    cout << "W - Move Up\n";
    cout << "A - Move Left\n";
    cout << "S - Move Down\n";
    cout << "D - Move Right\n";
    cout << "X - Quit Game\n";
    cout << "\033[37m\n"; // Reset color to white
}

class game {
protected:
    int width, height, score;
    Direction dir;
    bool gameOver;

public:
    game() {
        width = 20;
        height = 20;
        score = 0;
        dir = STOP;
        gameOver = false;
    }
};

class snake : protected game {
protected:
    int snakeX, snakeY;
    int* TailX;
    int* TailY;
    int Tail_length;

public:
    snake() {
        snakeX = width / 2;
        snakeY = height / 2;
        Tail_length = 0;
        TailX = new int[100];
        TailY = new int[100];
    }
};

class fruit : protected snake {
protected:
    int fruitX, fruitY;
    char foodSymbol;

public:
    fruit() {
        genFruit();
    }

    void genFruit() {
        fruitX = rand() % width;
        fruitY = rand() % height;
        char symbols[] = {'$', '%', '@'};
        foodSymbol = symbols[rand() % 3];
    }

    char getFoodSymbol() { return foodSymbol; }
    int getFruitX() { return fruitX; }
    int getFruitY() { return fruitY; }
};

class Main : protected fruit {
public:
    void MainGame(bool showGameOver = false) {
        system(CLEAR);

        int padding = 2; // Extra padding for a square shape
        for (int i = 0; i < padding; i++) cout << endl; // Top padding

        // Top boundary with spaces between #
        cout << "\033[34m"; // Set color to blue
        for (int i = 0; i < width + 2; i++) cout << "# ";
        cout << "\033[37m" << endl; // Reset color to white

        for (int i = 0; i < height; i++) {
            cout << "\033[34m#\033[37m "; // Left boundary
            for (int j = 0; j < width; j++) {
                if (showGameOver && i == height / 2 && j == (width / 2) - 4) {
                    cout << "\033[31mGAME OVER\033[37m"; // Red "GAME OVER"
                    j += 8; // Prevent overwriting
                }
                else if (j == snakeX && i == snakeY) {
                    cout << "\033[32mO\033[37m "; // Green for snake
                }
                else if (j == fruitX && i == fruitY) {
                    cout << "\033[31m" << getFoodSymbol() << "\033[37m "; // Red for fruit
                }
                else {
                    bool find = false;
                    for (int k = 0; k < Tail_length; k++) {
                        if (TailX[k] == j && TailY[k] == i) {
                            cout << "\033[32mo\033[37m "; // Green for tail
                            find = true;
                        }
                    }
                    if (!find) cout << "  "; // Maintain spacing
                }
            }
            cout << "\033[34m#\033[37m" << endl; // Right boundary
        }

        // Bottom boundary with spaces between #
        cout << "\033[34m"; // Set color to blue
        for (int i = 0; i < width + 2; i++) cout << "# ";
        cout << "\033[37m" << endl; // Reset color to white

        for (int i = 0; i < padding; i++) cout << endl; // Bottom padding

        cout << "Score: " << score << endl;
    }

    void updateGame() {
        if (dir == STOP) return;

        int prevX = TailX[0], prevY = TailY[0], prevXX, prevYY;
        TailX[0] = snakeX;
        TailY[0] = snakeY;

        for (int i = 1; i < Tail_length; i++) {
            prevXX = TailX[i];
            prevYY = TailY[i];
            TailX[i] = prevX;
            TailY[i] = prevY;
            prevX = prevXX;
            prevY = prevYY;
        }

        switch (dir) {
            case LEFT:  snakeX--; break;
            case RIGHT: snakeX++; break;
            case UP:    snakeY--; break;
            case DOWN:  snakeY++; break;
        }

        if (snakeX >= width || snakeX < 0 || snakeY >= height || snakeY < 0)
            gameOver = true;

        for (int i = 0; i < Tail_length; i++)
            if (TailX[i] == snakeX && TailY[i] == snakeY)
                gameOver = true;

        if (snakeX == fruitX && snakeY == fruitY) {
            score += 1;
            genFruit();
            Tail_length++;
        }
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': if (dir != RIGHT) dir = LEFT; break;
                case 'd': if (dir != LEFT) dir = RIGHT; break;
                case 'w': if (dir != DOWN) dir = UP; break;
                case 's': if (dir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    }

    bool isGameOver() { return gameOver; }
};

int difficulty() {
    int dif, choice;
    cout << "\n SET DIFFICULTY \n 1 : EASY\n 2 : MEDIUM\n 3 : HARD "
            "\n Choose difficulty: ";
    cin >> choice;

    switch (choice) {
        case 1: dif = 250; break;
        case 2: dif = 200; break;
        case 3: dif = 150; break;
        default: dif = 100;
    }
    return dif;
}

int main() {
    srand(time(0)); // Ensure random seed is set

    showIntro(); // Show welcome message and controls

    int play;
    do {
        int dif = difficulty();
        Main snakeGame;
        
        while (!snakeGame.isGameOver()) {
            snakeGame.MainGame();
            snakeGame.input();
            snakeGame.updateGame();
            Sleep(dif);
        }

        // Show "GAME OVER" on the board
        snakeGame.MainGame(true);
        Sleep(2000);

        cout << "Game Over!" << endl;
        cout << "Do you want to restart the game? Press 1 to start again, any other key to exit." << endl;
        cin >> play;
    } while (play == 1);

return 0;
}