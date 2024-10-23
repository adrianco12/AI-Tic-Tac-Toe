#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// prints the tic tac toe grid
void printGrid(char grid[4][4]) {
    for (int row = 1; row < 4; ++row) {
        cout << "+---+---+---+ \n";
        for (int col = 1; col < 4; ++col) {
            cout << "| " << grid[row][col] << " ";
        }
        cout << "|\n";
    }
    cout << "+---+---+---+\n\n";
}

// validates data input from user
void dataValidation(int &col, int &row) {
    while (col < 1 || col > 3 || row < 1 || row > 3) {
        cout << "Error. That is not a valid row/column. Pick a row (1, 2, 3): ";
        cin >> row;

        cout << "Pick a column (1, 2, 3): ";
        cin >> col;
        cout << endl;
    }
}

// checks if the spot the user takes is already taken
bool occupiedCheck(char grid[4][4], int col, int row) {
    return (grid[row][col] == 'X' || grid[row][col] == 'O');
}

// determines if there is a winner, or if it is a tie
bool checkWin(char grid[4][4], char player) {
    // Check rows and columns
    for (int i = 1; i < 4; i++) {
        if ((grid[i][1] == player && grid[i][2] == player && grid[i][3] == player) ||
            (grid[1][i] == player && grid[2][i] == player && grid[3][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((grid[1][1] == player && grid[2][2] == player && grid[3][3] == player) ||
        (grid[3][1] == player && grid[2][2] == player && grid[1][3] == player)) {
        return true;
    }
    return false;
}

// Check if the board is full
bool isBoardFull(char grid[4][4]) {
    for (int row = 1; row < 4; row++) {
        for (int col = 1; col < 4; col++) {
            if (grid[row][col] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Minimax function to determine the best move for the AI
int minimax(char grid[4][4], bool isMaximizing) {
    if (checkWin(grid, 'O')) return 1;   // AI wins
    if (checkWin(grid, 'X')) return -1;  // Player wins
    if (isBoardFull(grid)) return 0;      // Draw

    if (isMaximizing) {
        int bestScore = -1000;
        for (int row = 1; row < 4; row++) {
            for (int col = 1; col < 4; col++) {
                if (grid[row][col] == ' ') {
                    grid[row][col] = 'O'; // AI move
                    int score = minimax(grid, false);
                    grid[row][col] = ' '; // Undo move
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int row = 1; row < 4; row++) {
            for (int col = 1; col < 4; col++) {
                if (grid[row][col] == ' ') {
                    grid[row][col] = 'X'; // Player move
                    int score = minimax(grid, true);
                    grid[row][col] = ' '; // Undo move
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

// Function for AI to make a move
void aiMove(char grid[4][4]) {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;
    for (int row = 1; row < 4; row++) {
        for (int col = 1; col < 4; col++) {
            if (grid[row][col] == ' ') {
                grid[row][col] = 'O'; // AI move
                int score = minimax(grid, false);
                grid[row][col] = ' '; // Undo move
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = row;
                    moveCol = col;
                }
            }
        }
    }
    grid[moveRow][moveCol] = 'O'; // Place AI move
}

// main method
int main() {
    char grid[4][4] = {{' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}}; // 2d array
    bool gameOver = false; // used to end game
    int col = 0, row = 0;

    cout << "Welcome to Tic Tac Toe" << endl;

    printGrid(grid);

    // begin loop
    while (!gameOver) {
        // Player's turn
        cout << "Player X's turn" << endl << "Pick a row (1, 2, 3): ";
        cin >> row;
        cout << "Pick a column (1, 2, 3): ";
        cin >> col;

        // Data validation
        dataValidation(col, row);
        while (occupiedCheck(grid, col, row)) {
            cout << endl << "ERROR: That spot is occupied. Player X's turn again." << endl;
            cout << "Pick a row (1, 2, 3): ";
            cin >> row;
            cout << "Pick a column (1, 2, 3): ";
            cin >> col;
            dataValidation(col, row);
        }

        // Place character in chosen spot
        grid[row][col] = 'X';
        printGrid(grid);

        // Check if there is a winner
        if (checkWin(grid, 'X')) {
            cout << "Player X has won the game! Congratulations! Game over." << endl;
            break;
        }
        
        if (isBoardFull(grid)) {
            cout << "The game is a tie. No one wins. Game over :(" << endl;
            break;
        }

        // AI's turn
        aiMove(grid);
        printGrid(grid);
        
        // Check if there is a winner
        if (checkWin(grid, 'O')) {
            cout << "Player O has won the game! Congratulations! Game over." << endl;
            break;
        }

        if (isBoardFull(grid)) {
            cout << "The game is a tie. No one wins. Game over :(" << endl;
            break;
        }
    }

    // end program
    cout << endl << "Bye!" << endl;
    return 0;
}

