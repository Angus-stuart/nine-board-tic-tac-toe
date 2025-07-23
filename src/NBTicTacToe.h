/* 
This file contains all of the logic that prints the board and manages the gameplay for the Nine Board Tic-Tac-Toe game.
*/
#ifndef NBTICTACTOE_H_
#define NBTICTACTOE_H_
#include "TicTacToe.h"
#include <random>
#include <iostream>

using namespace std;

// Structure to represent coordinates of the current board within the 3x3 grid of boards
struct Coordinate {
	int x;
	int y;
};


class NBTicTacToe {
public: 
    NBTicTacToe();
    int playerMenu();
    NBTicTacToe(int x, int y);
    void displayBoards();
    int play();
    void setNextBoard(int, int);
    void addMove(int, int, int); 
    bool getXMove(int&, int&);  // Abstracted to work with any board
    bool getOMove(int&, int&);  // Abstracted to work with any board
    bool smartPlayer(int&, int&);
    bool getXOMove(int&, int&);
private: 
    TicTacToe grid[3][3];
    Coordinate currentBoard;
};

// Constructor: seeds random and picks a random starting board
NBTicTacToe::NBTicTacToe() {
    srand(time(0));
    currentBoard.x = rand() % 3;
    currentBoard.y = rand() % 3;
}

// Display menu and get player's choice of game mode
int NBTicTacToe::playerMenu() {
    int choice;
    bool correctInput = true;
    do {
        cout <<"Please choose a mode" << endl;
        cout << "1: Player VS Player" << endl;
        cout << "2: Player VS Random Player" << endl;
        cout << "0: Exit game" << endl;
        cin >> choice;
        switch (choice) {
            case 1: 
                return 1;
            case 2:
                return 2;
            case 0:
                return 0;
            default:
                correctInput = false;
                cout << "Invalid input try again." << endl;
        }
    } while (!correctInput);

    return 0;
}

// Prints all 9 boards in a grid, highlighting the current active board
void NBTicTacToe::displayBoards() {
    // Loop through each row of TicTacToe boards
    for (int row = 0; row < 3; row++) {
        // Print top borders of the boards
        for (int col = 0; col < 3; col++) {
            if (row == currentBoard.x && col == currentBoard.y) {
                cout << " * * * * * * ";  // Current board border
            } else {
                cout << " - - - - - - ";  // Regular border
            }
            if (col != 2) cout << "  ";  // Space between boards
        }
        cout << endl;

        // Print the Tic-Tac-Toe board rows
        for (int i = 0; i < 3; i++) { // Iterate over each row within a Tic-Tac-Toe board
            for (int col = 0; col < 3; col++) {
                if (col == currentBoard.y && row == currentBoard.x) {
                    cout << "* ";  // Current board left border
                } else {
                    cout << "| ";  // Regular left border
                }

                for (int j = 0; j < 3; j++) { // Iterate over each column within a Tic-Tac-Toe board
                    char playerSymbol = ' ';
                    int cellValue = grid[row][col].getCellValue(i, j);
                    if (cellValue == 1)
                        playerSymbol = 'X';
                    else if (cellValue == -1)
                        playerSymbol = 'O';
                    cout << playerSymbol;
                    if (j != 2) 
                        cout << " | "; // Space between cells
                }

                if (col == currentBoard.y && row == currentBoard.x) {
                    cout << " *";  // Current board right border
                } else {
                    cout << " |";  // Regular right border
                }

                if (col != 2) cout << "  ";  // Space between boards
            }
            cout << endl;

            if (i != 2) {  // Print horizontal separator within sub-boards
                for (int col = 0; col < 3; col++) {
                    if (col == currentBoard.y && row == currentBoard.x) {
                        cout << "* -   -   - *";
                    } else {
                        cout << "| -   -   - |";
                    }
                    if (col != 2) cout << "  ";  // Space between boards
                }
                cout << endl;
            }
        }

        // Print bottom borders of the boards
        for (int col = 0; col < 3; col++) {
            if (row == currentBoard.x && col == currentBoard.y) {
                cout << " * * * * * * ";  // Current board border
            } else {
                cout << " - - - - - - ";  // Regular border
            }
            if (col != 2) cout << "  ";  // Space between boards
        }
        cout << endl;
    }
    cout << endl;
}

// Get move from player O via console input; ensures valid move for current board
bool NBTicTacToe::getOMove(int& x, int& y) {
    int row, col;
    do {
        cin >> row >> col;
        cout << endl;
        if (!grid[currentBoard.x][currentBoard.y].isValidMove(row - 1, col - 1)) {
            cout << "Invalid move, please re-enter coordinates: ";
        }
    } while (!grid[currentBoard.x][currentBoard.y].isValidMove(row - 1, col - 1));

    x = row - 1;
    y = col - 1;
    return true;
}
// Generate a random valid move for player X on the current board
bool NBTicTacToe::getXMove(int& x, int& y) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!grid[currentBoard.x][currentBoard.y].isValidMove(row, col));

    x = row;
    y = col;
    cout << endl << "Player X move: " << x + 1 << ", " << y + 1 << endl;
    return true;
}

// Placeholder for smarter AI move logic
bool NBTicTacToe::smartPlayer(int& x, int& y) {
    int row, col;
	do {
		
	} while (!grid[currentBoard.x][currentBoard.y].isValidMove(row, col));
	x = row;
	y = col;

	return true;
}


// Get move input for either player X or O (human input), validating it
bool NBTicTacToe::getXOMove(int& x, int& y) {
	int row, col;
	do {
		cin >> row >> col;
		cout << endl;
		if (!grid[currentBoard.x][currentBoard.y].isValidMove(row - 1, col - 1)) {
			cout << "Invalid move please re-enter coordinates: ";
		}
	} while (!grid[currentBoard.x][currentBoard.y].isValidMove(row - 1, col - 1));
	x = row - 1;
	y = col - 1;

	return true;
}

// Add a move for a player to the current board and update move count
void NBTicTacToe::addMove(int x, int y, int player) {
    grid[currentBoard.x][currentBoard.y].addMove(x, y, player);
    
    grid[currentBoard.x][currentBoard.y].noOfMoves ++;
}

// Set the next board to play on if coordinates are valid
void NBTicTacToe::setNextBoard(int x, int y) {
     if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        currentBoard.x = x;
        currentBoard.y = y;
    }
}

// Main game loop that manages turns, input, and game state until completion
int NBTicTacToe::play() {
    int playerChoice = playerMenu();
    int player = 1;
    displayBoards(); // Display the initial empty boards
    int done = 0;

    while (done == 0) {
        char playerSymbol = (player == 1) ? 'X' : 'O';
        cout << "Player " << playerSymbol << " enter move: ";
        int x, y;
        if (playerChoice == 1) {
            getXOMove(x, y);
        }
        
        if (playerChoice == 2) {
            if (player == 1) {
                getXMove(x, y);
            } else if (player == -1) {
                getOMove(x, y);
            }
        }
       

        addMove(x, y, player);
        displayBoards(); // Display the boards after each move

        // Check if the current sub-board is won
        done = grid[currentBoard.x][currentBoard.y].gameStatus(); 
        int counter = 0;
        for (int row = 0; row < 3; row ++) {
            for (int col = 0; col < 3; col ++) {
                if (grid[row][col].gameStatus() == 2) {
                    counter ++;
                }

            }
        }
        if (counter >= 9) {
            cout << "All boards are full!!" << endl << "Thank you for playing long enough you managed to fill all 9 boards" << endl;
            done = 2;
        }
        // If the current sub-board is won, declare the winner and end the game
        if (done == 1) {
            cout << "Player X wins the game!" << endl;
            return 1;
        }
        if (done == -1) {
            cout << "Player O wins the game!" << endl;
            return -1;
        }

        // If the current sub-board is a draw, check if the entire grid has no more moves
        if (done == 2) {
            cout << "Sub-board is a draw! Random board selected" << endl; 
            currentBoard.x = rand() % 3;
            currentBoard.y = rand() % 3;
            done = 0;
        }

        // Switch to the next player
        player = -player;
        if (done != 2) {
            setNextBoard(x, y);
            displayBoards();
        }

        
    }

    return 0;
}

#endif