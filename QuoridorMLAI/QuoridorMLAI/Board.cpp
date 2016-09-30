#include "Board.h"

// Square containing booleans because its easier



// the actual game board


// Constructor for setting up the board
Board::Board() {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++) {
			gb.board[row][col].row = row;
			gb.board[row][col].col = col;
			gb.board[row][col].seen = false;
		}
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

bool Board::checkNotBlocked(int player) {
	queue<Square> q;
	bool check = false;
	// check player 1
	gb.board[pOne.row][pOne.col].seen = true;
	q.push(gb.board[pOne.row][pOne.col]);	
	while (!q.empty()) {
		Square temp = q.front();
		q.pop();
		if (temp.row == 8) {
			check = true;
			break;
		}
		if (temp.up && !gb.board[temp.row - 1][temp.col].seen) {
			gb.board[temp.row - 1][temp.col].seen = true;
			q.push(gb.board[temp.row - 1][temp.col]);
		}
		if (temp.down && !gb.board[temp.row + 1][temp.col].seen) {
			gb.board[temp.row + 1][temp.col].seen = true;
			q.push(gb.board[temp.row + 1][temp.col]);
		}
		if (temp.left && !gb.board[temp.row][temp.col - 1].seen) {
			gb.board[temp.row][temp.col - 1].seen = true;
			q.push(gb.board[temp.row][temp.col - 1]);
		}
		if (temp.right && !gb.board[temp.row][temp.col + 1].seen) {
			gb.board[temp.row][temp.col + 1].seen = true;
			q.push(gb.board[temp.row][temp.col + 1]);
		}
	}
	while (!q.empty())
		q.pop();
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			gb.board[row][col].seen = false;
	if (!check)
		return check;
	check = false;
	// check player 2
	q.push(gb.board[pTwo.row][pTwo.col]);
	gb.board[pTwo.row][pTwo.col].seen = true;
	while (!q.empty()) {
		Square temp = q.front();
		q.pop();
		if (temp.row == 0) {
			check = true;
			break;
		}
		if (temp.up && !gb.board[temp.row - 1][temp.col].seen) {
			gb.board[temp.row - 1][temp.col].seen = true;
			q.push(gb.board[temp.row - 1][temp.col]);
		}
		if (temp.down && !gb.board[temp.row + 1][temp.col].seen) {
			gb.board[temp.row + 1][temp.col].seen = true;
			q.push(gb.board[temp.row + 1][temp.col]);
		}
		if (temp.left && !gb.board[temp.row][temp.col - 1].seen) {
			gb.board[temp.row][temp.col - 1].seen = true;
			q.push(gb.board[temp.row][temp.col - 1]);
		}
		if (temp.right && !gb.board[temp.row][temp.col + 1].seen) {
			gb.board[temp.row][temp.col + 1].seen = true;
			q.push(gb.board[temp.row][temp.col + 1]);
		}
	}

	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			gb.board[row][col].seen = false;
	return check;
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
			if (!checkNotBlocked(player)) {
				gb.board[row][col].down = true;
				gb.board[row][col + 1].down = true;
				gb.board[row + 1][col].up = true;
				gb.board[row + 1][col + 1].up = true;
				return false;
			}
		} else
			return false;
	} else {
		for (int i = 0; i < wallCounter; i++) {
			if (walls[i].row == row && walls[i].col == col && walls[i].dir.compare("h") == 0)
				return false;
		}
		if (row < 8 && gb.board[row][col].right && gb.board[row + 1][col].right) {
			gb.board[row][col].right = false;
			gb.board[row + 1][col].right = false;
			gb.board[row][col + 1].left = false;
			gb.board[row + 1][col + 1].left = false;
			if (!checkNotBlocked(player)) {
				gb.board[row][col].right = true;
				gb.board[row + 1][col].right = true;
				gb.board[row][col + 1].left = true;
				gb.board[row + 1][col + 1].left = true;
				return false;
			}
		} else
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
	if (move.compare("upleft") == 0)
		d = UPLEFT;
	if (move.compare("upright") == 0)
		d = UPRIGHT;
	if (move.compare("downleft") == 0)
		d = DOWNLEFT;
	if (move.compare("downright") == 0)
		d = DOWNRIGHT;
	if (move.compare("leftup") == 0)
		d = LEFTUP;
	if (move.compare("leftdown") == 0)
		d = LEFTDOWN;
	if (move.compare("rightup") == 0)
		d = RIGHTUP;
	if (move.compare("rightdown") == 0)
		d = RIGHTDOWN;
	if (player == 1)
		return PawnMove(pOne, d, player);
	else
		return PawnMove(pTwo, d, player);
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

bool Board::checkWinner() {
	if (pOne.row == 8 || pTwo.row == 0)
		return true;
	return false;
}

string Board::getWinner() {
	if (pOne.row == 8)
		return "Player 1";
	if (pTwo.row == 0)
		return "Player 2";
	return "No winner yet.";
}

// takes a player pawn and a direction d and moves it
bool Board::PawnMove(Pawn &player, Direction d, int p) {
	bool up, down, left, right;
	if (p == 1) {
		up = player.row - 1 == pTwo.row && player.col == pTwo.col;
		down = player.row + 1 == pTwo.row && player.col == pTwo.col;
		left = player.col - 1 == pTwo.col && player.row == pTwo.row;
		right = player.col + 1 == pTwo.col && player.row == pTwo.row;
	}
	else {
		up = player.row - 1 == pOne.row && player.col == pOne.col;
		down = player.row + 1 == pOne.row && player.col == pOne.col;
		left = player.col - 1 == pOne.col && player.row == pOne.row;
		right = player.col + 1 == pOne.col && player.row == pOne.row;
	}
	switch (d) {
	case Board::UP:
		if (up && gb.board[player.row - 1][player.col].up) {
			player.row -= 2;
			return true;
		} 
		if (gb.board[player.row][player.col].up && !up) {
			player.row -= 1;
			return true;
		}
		return false;
	case Board::DOWN:		 
		if (down && gb.board[player.row + 1][player.col].down) {
			player.row += 2;
			return true;
		}
		if (gb.board[player.row][player.col].down && !down) {
			player.row += 1;
			return true;
		}
		return false;
	case Board::LEFT:
		if (left && gb.board[player.row][player.col - 1].left) {
			player.col -= 2;
			return true;
		}
		if (gb.board[player.row][player.col].left && !left) {
			player.col -= 1;
			return true;
		}
		return false;
	case Board::RIGHT:
		if (right && gb.board[player.row][player.col + 1].right) {
			player.col += 2;
			return true;
		}
		if (gb.board[player.row][player.col].right && !right) {
			player.col += 1;
			return true;
		}
		return false;
	case Board::UPLEFT:
		if (up && !gb.board[player.row - 1][player.col].up) {
			player.row -= 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::UPRIGHT:
		if (up && !gb.board[player.row - 1][player.col].up) {
			player.row -= 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::DOWNLEFT:
		if (down && !gb.board[player.row + 1][player.col].down) {
			player.row += 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::DOWNRIGHT:
		if (down && !gb.board[player.row + 1][player.col].down) {
			player.row += 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::LEFTUP:
		if (left && !gb.board[player.row][player.col - 1].left) {
			player.row -= 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::LEFTDOWN:
		if (left && !gb.board[player.row][player.col - 1].left) {
			player.row += 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::RIGHTUP:
		if (right && !gb.board[player.row][player.col + 1].right) {
			player.row -= 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::RIGHTDOWN:
		if (right && !gb.board[player.row][player.col + 1].right) {
			player.row += 1;
			player.col += 1;
			return true;
		}
		return false;
	default:
		return false;
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