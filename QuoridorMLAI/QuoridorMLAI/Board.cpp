#include "Board.h"

// Square containing booleans because its easier
struct Square {	
	bool up, down, left, right;
};

// The game board of squares
struct GameBoard {
	Square board[9][9];
};


// the actual game board
GameBoard gb;

// Constructor for setting up the board
Board::Board() {	
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (row != 0) // Top Wall
				gb.board[row][col].up    = true;
			if (row != 8) // Bottom Wall
				gb.board[row][col].down  = true;
			if (col != 0) // Left Wall
				gb.board[row][col].left  = true;
			if (col != 8) // Right Wall
				gb.board[row][col].right = true;
		}
	}
	setPawns();
}

// places walls if placeable
bool Board::placeWalls(int player, int row, int col, string dir) {
	if (player == 1) {
		if (pOne.wallsLeft > 0)
			pOne.wallsLeft--;
		else
			return false;
	} else {
		if (pTwo.wallsLeft > 0)
			pTwo.wallsLeft--;
		else
			return false;
	}
	if (dir.compare("h") == 0) {
		for (int i = 0; i < wallCounter; i++) {
			if (walls[i].row == row && walls[i].col == col && walls[i].dir.compare("v") == 0)
				return false;
		}
		if (col < 8 && gb.board[row][col].down && gb.board[row][col + 1].down) {
			gb.board[row][col].down = false;
			gb.board[row][col + 1].down = false;
			gb.board[row + 1][col].up = false;
			gb.board[row + 1][col + 1].up = false;
		}
		else
			return false;
	} else {
		for (int i = 0; i < wallCounter; i++) {
			if (walls[i].row == row && walls[i].col == col && walls[i].dir.compare("h") == 0)
				return false;
		}
		if (row < 8 && gb.board[row][col].right && gb.board[row][col + 1].right) {
			gb.board[row][col].right = false;
			gb.board[row + 1][col].right = false;
			gb.board[row][col + 1].left = false;
			gb.board[row + 1][col + 1].left = false;
		}
		else
			return false;
	}
	Wall temp;
	temp.row = row;
	temp.col = col;
	temp.dir = dir;
	walls[wallCounter] = temp;
	wallCounter++;

	return true;
}

// moves the pawn
bool Board::movePawn(int player, string move) {
	Direction d;
	if (move.compare("up") == 0)
		d = UP;
	if (move.compare("down") == 0)
		d = DOWN;
	if (move.compare("left") == 0)
		d = LEFT;
	if (move.compare("right") == 0)
		d = RIGHT;
	if (player == 1)
		return PawnMove(pOne, d);
	else
		return PawnMove(pTwo, d);
}

// sets pawns location
void Board::setPawns() {
	// make and placepOne
	pOne.row = 0;
	pOne.col = 4;
	// make and place pTwo
	pTwo.row = 8;
	pTwo.col = 4;
}

// takes a player pawn and a direction d and moves it
bool Board::PawnMove(Pawn &player, Direction d) {
	switch (d) {
	case Board::UP:
		if (gb.board[player.row][player.col].up) {
			player.row -= 1;
			return true;
		}
		return false;
	case Board::DOWN:
		if (gb.board[player.row][player.col].down) {
			player.row += 1;
			return true;
		}
		return false;
	case Board::LEFT:
		if (gb.board[player.row][player.col].left) {
			player.col -= 1;
			return true;
		}
		return false;
	case Board::RIGHT:
		if (gb.board[player.row][player.col].right) {
			player.col += 1;
			return true;
		}
		return false;
	default:
		return false;
		break;
	}
}


// function to print the board to console with
string Board::PrintBoard() {
	string board = " GAME OF QUORIDOR\n+-+-+-+-+-+-+-+-+-+";
	for (int row = 0; row < 9; row++) {
		board += "\n|";
		for (int col = 0; col < 9; col++) {
			if (row == pOne.row && col == pOne.col)
				board += "1";
			else if (row == pTwo.row && col == pTwo.col)
				board += "2";
			else
				board += " ";
			// if right != " " print "|"			
			if (!gb.board[row][col].right)
				board += "|";
			else // there is no right wall print " " for wall space  
				board += " ";
			
		}
		board += "\n";
		for (int col = 0; col < 9; col++) {
			// if down != " " theres a wall print "+-"
			if (!gb.board[row][col].down)
				board += "+-";
			else // theres no down wall print self or "+ "
				board += "+ ";
		}
		board += "+";
	}
	return board;
}