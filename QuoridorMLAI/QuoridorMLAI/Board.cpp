#include "Board.h"

// Node with ascii value
struct Node {
	string asci;
};

// Square containing pointers to other squares nodes because
// C++ is dumb
struct Square {	
	Node self, up, down, left, right;
};

// The game board of squares
struct GameBoard {
	Square board[9][9];
};


struct Pawn {
	int row;
	int col;
};

// the actual game board
GameBoard gb;

// Constructor for setting up the board
Board::Board() {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			gb.board[row][col].self.asci = " ";
	
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (row != 0) // Top Wall
				gb.board[row][col].up    = gb.board[row - 1][col].self;
			if (row != 8) // Bottom Wall
				gb.board[row][col].down  = gb.board[row + 1][col].self;
			if (col != 0) // Left Wall
				gb.board[row][col].left  = gb.board[row][col - 1].self;
			if (col != 8) // Right Wall
				gb.board[row][col].right = gb.board[row][col + 1].self;
		}
	}
	setPawns();
}
Pawn pOne, pTwo;


void Board::setPawns() {
	// make and placepOne
	pOne.row = 0;
	pOne.col = 4;
	placePawn(0, 4);
	// make and place pTwo
	pTwo.row = 8;
	pTwo.col = 4;
	placePawn(8, 4);
}

void Board::placePawn(int row, int col) {
	gb.board[row][col].self.asci = "o";
}

void Board::removePawn(int row, int col) {
	gb.board[row][col].self.asci = " ";
}

// function to print the board to console with
string Board::toString() {
	string board = " GAME OF QUORIDOR\n+-+-+-+-+-+-+-+-+-+";
	for (int row = 0; row < 9; row++) {
		board += "\n|";
		for (int col = 0; col < 9; col++) {
			board += gb.board[row][col].self.asci;
			// if right != " " print "|"
			if (gb.board[row][col].right.asci.compare(" "))
				board += "|";
			else // there is no right wall print " " for wall space  
				board += " ";
			
		}
		board += "\n";
		for (int col = 0; col < 9; col++) {
			// if down != " " theres a wall print "+-"
			if (gb.board[row][col].down.asci.compare(" "))
				board += "+-";
			else // theres no down wall print self or "+ "
				board += "+ ";
		}
		board += "+";
	}
	return board;
}