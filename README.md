# Tetris Game

## Introduction
This is a console-based Tetris game implemented in C++ that follows the classic gameplay mechanics of Tetris. Players control falling tetrominoes, positioning and rotating them to form complete horizontal lines. When a line is completed, it disappears, and the player earns points. The game increases in speed as the score rises, making it more challenging over time. The objective is to prevent the stack of tetrominoes from reaching the top of the board.

## Overview
This is a simple console-based Tetris game implemented in C++ using basic graphics with ANSI escape codes. The game supports keyboard controls for moving and rotating tetrominoes and includes a scoring system, increasing difficulty, and a replay option.

## Features
- **7 Classic Tetromino Shapes**: Includes I, O, T, S, Z, J, and L pieces.
- **Smooth Controls**: Move left, right, rotate, and drop instantly.
- **Scoring System**: Earn points by clearing lines.
- **Dynamic Difficulty**: The game speeds up as you score more.
- **Color-Coded Blocks**: Each tetromino has a distinct color.
- **Game Over and Restart Option**: Prompt to replay after losing.

## Code for The Game
< >
## Controls
| Key         | Action                   |
|------------|--------------------------|
| Left Arrow  | Move left               |
| Right Arrow | Move right              |
| Down Arrow  | Move down               |
| Up Arrow    | Rotate                  |
| Spacebar    | Instant drop            |
| ESC         | Quit game               |


### Linux (with `ncurses`):
1. Install `ncurses` if not already installed:
   ```sh
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```
2. Compile and run the game:
   ```sh
   g++ -o tetris tetris.cpp -std=c++11 -lncurses
   ./tetris
   ```

## Dependencies And OS switch
- Uses `<conio.h>` and `<windows.h>`, making it best suited for Windows.
- For Linux, replace `<conio.h>` and `_kbhit()` with `ncurses`.
- 
## Screenshots of the Game
- When Score Increases
![Screenshot 2025-03-27 022146](https://github.com/user-attachments/assets/381ddccc-b922-45f1-aad7-489d42c34336)
- When Game Gets Over
![Screenshot 2025-03-27 022026](https://github.com/user-attachments/assets/f7a3af4b-0618-4bd6-a914-1b92e57c1821)

## Issues
- The game may not work on some Linux terminals without modification.
- The game logic runs on a single-threaded loop, so input handling can be slightly delayed.

## Future Improvements
- Add a graphical interface using SDL or SFML.
- Implement multiplayer or online leaderboard.
- Improve AI for better tetromino placement suggestions.

## License
This project is open-source under the MIT License.

## Members Of Project
- Kavya Halani
- Vrinda Goradia
- Ishit Shripal
- Riya Soni

---
### Enjoy playing Tetris! 🎮

