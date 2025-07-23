/*
This file defines the TicTacToe class, which represents a single 3x3 Tic-Tac-Toe board.
It includes functionality to:
- Initialize and manage the game board state,
- Validate moves,
- Add moves for players,
- Check the game status (win, draw, ongoing),
- Access cell values.

This class is used as a building block for the larger Nine Board TicTacToe game.
*/
#ifndef TICTACTOE_H_
#define TICTACTOE_H_

const int BOARDSIZE = 3;

class TicTacToe {
private:
	int board[BOARDSIZE][BOARDSIZE];
public:
	TicTacToe();
	bool isValidMove(int, int);
    void addMove(int x, int y, int player);
	int gameStatus();
	void displayBoard();
	int getCellValue(int, int);
	int noOfMoves;
};



// Constructor: initializes board to all zeros and resets move count
TicTacToe::TicTacToe() : noOfMoves(0){
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			board[row][col] = 0;

}

// Returns value in cell or 0 if out of bounds
int TicTacToe::getCellValue(int x, int y) {
    if (x >= 0 && x < BOARDSIZE && y >= 0 && y < BOARDSIZE) {
        return board[x][y]; 
    }
    return 0;
}

// Checks if the move is within bounds and the cell is empty
bool TicTacToe::isValidMove(int x, int y) {
	if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0) { 
        return false;
    }
    else {
		return true;
	}
}

// Sets the cell to player's symbol (1 for X, -1 for O)
void TicTacToe::addMove(int x, int y, int player) {
    board[x][y] = player;
}

// Checks for a winner or draw on this board
// Returns:
//   1 if player X wins
//  -1 if player O wins
//   2 if draw (all moves used, no winner)
//   0 if game ongoing
int TicTacToe::gameStatus() {
    // Check rows for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0]; 
        }
    }
    
    // Check columns for a win
    for (int i = 0; i < 3; i++) {
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i]; 
        }
    }

    // Check top left to bottom right diagonal 
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }

    // Check top right to bottom left diagonal
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    // Checks if board is full
    if (noOfMoves >= 9) {
        return 2;
    }
    return 0;
}

#endif
