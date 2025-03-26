#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

char TETROMINOS[7][4][4] = {
    { // I
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // O
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // T
        {' ', '#', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // S
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // Z
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // J
        {'#', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    { // L
        {' ', ' ', '#', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    }
};

// ANSI color codes
const char* colors[7] = {
    "\033[36m", // Cyan for I
    "\033[33m", // Yellow for O
    "\033[35m", // Magenta for T
    "\033[32m", // Green for S
    "\033[31m", // Red for Z
    "\033[34m", // Blue for J
    "\033[91m"  // Bright Red for L
};

class Tetromino {
public:
    char shape[4][4];
    int x, y, type;

    Tetromino() {
        x = WIDTH / 2 - 2;
        y = 0;
        type = rand() % 7;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = TETROMINOS[type][i][j];
    }

    void rotate() {
        char rotated[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rotated[j][3 - i] = shape[i][j];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = rotated[i][j];
    }
};

class Board {
public:
    char grid[HEIGHT][WIDTH] = {};
    int colorGrid[HEIGHT][WIDTH] = {}; // Store colors
    int score = 0;

    Board() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++) {
                grid[i][j] = ' ';
                colorGrid[i][j] = -1; // No color initially
            }
    }

    void draw(Tetromino &tetro) {
        system("cls");

        for (int i = 0; i < HEIGHT; i++) {
            cout << "|";
            for (int j = 0; j < WIDTH; j++) {
                bool isTetromino = false;

                for (int ti = 0; ti < 4; ti++)
                    for (int tj = 0; tj < 4; tj++)
                        if (tetro.shape[ti][tj] == '#' && tetro.y + ti == i && tetro.x + tj == j)
                            isTetromino = true;

                if (isTetromino)
                    cout << colors[tetro.type] << "#" << "\033[0m"; // Active Tetrimino color
                else if (grid[i][j] == '#')
                    cout << colors[colorGrid[i][j]] << "#" << "\033[0m"; // Retain placed color
                else
                    cout << " ";
            }
            cout << "|" << endl;
        }
        cout << string(WIDTH + 2, '-') << endl;
        cout << "Score: \033[33m" << score << "\033[0m" << endl;
        cout << "Use Arrow Keys to Move, SPACE to Drop, ESC to Quit\n";
    }

    bool isValidMove(Tetromino &tetro, int newX, int newY) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (tetro.shape[i][j] == '#' &&
                    (newY + i >= HEIGHT || newX + j < 0 || newX + j >= WIDTH || grid[newY + i][newX + j] == '#'))
                    return false;
        return true;
    }

    void placeTetromino(Tetromino &tetro) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (tetro.shape[i][j] == '#') {
                    grid[tetro.y + i][tetro.x + j] = '#';
                    colorGrid[tetro.y + i][tetro.x + j] = tetro.type; // Store color type
                }
    }

    void clearLines() {
        int linesCleared = 0;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++)
                if (grid[i][j] == ' ') {
                    full = false;
                    break;
                }

            if (full) {
                linesCleared++;
                for (int k = i; k > 0; k--) {
                    for (int j = 0; j < WIDTH; j++) {
                        grid[k][j] = grid[k - 1][j];
                        colorGrid[k][j] = colorGrid[k - 1][j]; // Shift colors down
                    }
                }

                for (int j = 0; j < WIDTH; j++) {
                    grid[0][j] = ' ';
                    colorGrid[0][j] = -1; // Clear color
                }
                i++;
            }
        }
        score += linesCleared * 100;
    }
};
void displayGameOverScreen(int score);
class Game {
    Board board;
    Tetromino tetro;
    bool gameOver;
    int speed;

public:
    Game() {
        gameOver = false;
        speed = 300;
    }

    void updateSpeed() {
        if (board.score > 0) {
            speed = max(50, 500 - (board.score / 200) * 50);
        }
    }

    void run() {
        while (!gameOver) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 27) {
                    gameOver = true;
                    cout << "Game Quit!\n";
                    break;
                }
                if (ch == ' ') {
                    while (board.isValidMove(tetro, tetro.x, tetro.y + 1))
                        tetro.y++;
                }
                if (ch == -32) {
                    ch = _getch();
                    if (ch == 75 && board.isValidMove(tetro, tetro.x - 1, tetro.y))
                        tetro.x--;
                    else if (ch == 77 && board.isValidMove(tetro, tetro.x + 1, tetro.y))
                        tetro.x++;
                    else if (ch == 80 && board.isValidMove(tetro, tetro.x, tetro.y + 1))
                        tetro.y++;
                    else if (ch == 72) {
                        tetro.rotate();
                        if (!board.isValidMove(tetro, tetro.x, tetro.y))
                            tetro.rotate();
                    }
                }
            }

            if (board.isValidMove(tetro, tetro.x, tetro.y + 1)) {
                tetro.y++;
            } else {
                board.placeTetromino(tetro);
                board.clearLines();
                updateSpeed();
                tetro = Tetromino();

                if (!board.isValidMove(tetro, tetro.x, tetro.y)) {
                    gameOver = true;
                    displayGameOverScreen(board.score); // Show "GAME OVER" in the center
                    askPlayAgain(); // Ask to replay
                    return;
                }
                
            }

            board.draw(tetro);
            Sleep(speed);
        }
    }
    void askPlayAgain(){
        cout<<"Do you want to play again? (Y/N):";
        char ch= _getch();
        if(ch=='Y'|| ch=='y'){
            resetGame();
            run();
        }else{
            cout<<"Thanks for playing"<<endl;
        }
    }
    void resetGame(){
        board= Board();
        tetro= Tetromino();
        gameOver=false;
    }
};
void displayStartScreen(){
    system("cls");
    cout<<"Welcome To Tetris!"<<endl;
    cout<<"Press any key to start..."<<endl;
    _getch();
}
void displayGameOverScreen(int score) {
    system("cls");
    
    for (int i = 0; i < HEIGHT / 2 - 1; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) cout << " ";
        cout << "|" << endl;
    }

    cout << "|";
    int padding = (WIDTH - 10) / 2; // Centering "GAME OVER"
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "\033[31mGAME OVER\033[0m"; // Red "GAME OVER" message
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "|" << endl;

    for (int i = HEIGHT / 2; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) cout << " ";
        cout << "|" << endl;
    }

    cout << string(WIDTH + 2, '-') << endl;
    cout << "Final Score: \033[33m" << score << "\033[0m" << endl;
}


int main() {
    srand(time(0));
    displayStartScreen();
    Game game;
    game.run();
  return 0;
}
