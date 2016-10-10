#include "Board.h"

// Constructs the board
Board::Board() {

	// Initialize board pieces
	wallCounter = 0;
	gb = new GameBoard;
	setPawns();

	// sets up the board
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++) {
			gb->board[row][col] = new Square;
			gb->board[row][col]->row = row;
			gb->board[row][col]->col = col;
			gb->board[row][col]->seen = false;
			if (row != 0) // Top Wall
				gb->board[row][col]->up = true;
			else
				gb->board[row][col]->up = false;
			if (row != 8) // Bottom Wall
				gb->board[row][col]->down = true;
			else
				gb->board[row][col]->down = false;
			if (col != 0) // Left Wall
				gb->board[row][col]->left = true;
			else
				gb->board[row][col]->left = false;
			if (col != 8) // Right Wall
				gb->board[row][col]->right = true;
			else
				gb->board[row][col]->right = false;
		}
}

// Returns: the board as a string
string Board::toString() {
	string board = "\n     GAME OF QUORIDOR\n\n    0 1 2 3 4 5 6 7 8\n   +-+-+-+-+-+-+-+-+-+";
	for (int row = 0; row < 9; row++) {
		board += "\n " + to_string(row) + " |";
		for (int col = 0; col < 9; col++) {
			if (row == pOne->row && col == pOne->col)
				board += "1";
			else if (row == pTwo->row && col == pTwo->col)
				board += "2";
			else
				board += " ";
			// if right != true print "|"			
			if (!gb->board[row][col]->right)
				board += "|";
			else // there is no right wall print " " for wall space  
				board += " ";

		}
		board += "\n   ";
		for (int col = 0; col < 9; col++) {
			// if down != " " theres a wall print "+-"			
			if (!gb->board[row][col]->down)
				board += "+-";
			else // theres no down wall print self or "+ "
				board += "+ ";
		}
		board += "+";
	}
	return board;
}

// Returns: a string for printing the winner
string Board::getWinner() {
	if (pOne->row == 8)
		return "Player 1";
	if (pTwo->row == 0)
		return "Player 2";
	return "No winner yet.";
}

// Parameters: player - the player whos pawn made a move
//               move - the direction the player chose to move
// Post-Condition: moves a pawn
// Returns: true if successful false otherwise
bool Board::movePawn(int player, string move) {
	// convert the move to an enum for PawnMove switches
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
		return PawnMove(*pOne, d, player);
	else
		return PawnMove(*pTwo, d, player);
}

// Parameters:    player - the player whos pawn made a move
//                   row - the row the wall is attempted to be placed at
//                   col - the column the wall is attempted to be placed at
//             direction - the direction of the wall (horizontal, vertical)
// Post-Condition: places a wall
// Returns: true if successful false otherwise
bool Board::placeWalls(int player, int row, int col, string dir) {
	// does the player have a wall left to place
	if (player == 1) {
		if (pOne->wallsLeft == 0)			
			return false;
	} else {
		if (pTwo->wallsLeft == 0)			
			return false;
	}

	// Already have a wall at this location
	for (int i = 0; i < wallCounter; i++)
		if (walls[i].row == row && walls[i].col == col)
			return false;

	// Check for type of wall to place
	if (dir.compare("h") == 0) {		
		// break the connections for the horizontal wall placement
		if (col < 8 && gb->board[row][col]->down && gb->board[row][col + 1]->down) {
			gb->board[row][col]->down = false;
			gb->board[row][col + 1]->down = false;
			gb->board[row + 1][col]->up = false;
			gb->board[row + 1][col + 1]->up = false;
			if (!checkNotBlocked()) { // did the wall block off a player
				gb->board[row][col]->down = true;
				gb->board[row][col + 1]->down = true;
				gb->board[row + 1][col]->up = true;
				gb->board[row + 1][col + 1]->up = true;
				return false;
			}
		} else
			return false;
	} else {
		// break the connections for the vertical wall placement
		if (row < 8 && gb->board[row][col]->right && gb->board[row + 1][col]->right) {
			gb->board[row][col]->right = false;
			gb->board[row + 1][col]->right = false;
			gb->board[row][col + 1]->left = false;
			gb->board[row + 1][col + 1]->left = false;
			if (!checkNotBlocked()) { // did the wall block off a player
				gb->board[row][col]->right = true;
				gb->board[row + 1][col]->right = true;
				gb->board[row][col + 1]->left = true;
				gb->board[row + 1][col + 1]->left = true;
				return false;
			}
		} else
			return false;
	}

	// does the player have a wall left to place
	if (player == 1)
		pOne->wallsLeft--;
	else
		pTwo->wallsLeft--;
	
	// Make the temp wall
	Wall temp;
	temp.row = row;
	temp.col = col;
	temp.dir = dir;

	// store the wall in the walls array
	walls[wallCounter] = temp;

	// increment the current location into the walls array
	wallCounter++;

	// Wall was successfully placed
	return true;
}

// Returns: true if there is a winner false otherwise
bool Board::checkWinner() {
	if (pOne->row == 8 || pTwo->row == 0)
		return true;
	return false;
}

// Post-Condition: Sets the pawns at their starting locations
void Board::setPawns() {
	pOne = new Pawn;
	pTwo = new Pawn;
	// make and placepOne
	pOne->row = 0;
	pOne->col = 4;
	pOne->wallsLeft = 10;
	// make and place pTwo
	pTwo->row = 8;
	pTwo->col = 4;
	pTwo->wallsLeft = 10;
}

// Parameters:        player - the pawn to be moved
//                 direction - the direction the player wants to move
//             currentPlayer - the current players number
// Post-Condition: alters a pawns location
// Returns: true if successful false otherwise
bool Board::PawnMove(Pawn &player, Direction d, int currentPlayer) {
	// Testing booleans for movements checks
	bool up, down, left, right;

	// Set testing booleans for movement checks
	if (currentPlayer == 1) {
		up = player.row - 1 == pTwo->row && player.col == pTwo->col;
		down = player.row + 1 == pTwo->row && player.col == pTwo->col;
		left = player.col - 1 == pTwo->col && player.row == pTwo->row;
		right = player.col + 1 == pTwo->col && player.row == pTwo->row;
	} else {
		up = player.row - 1 == pOne->row && player.col == pOne->col;
		down = player.row + 1 == pOne->row && player.col == pOne->col;
		left = player.col - 1 == pOne->col && player.row == pOne->row;
		right = player.col + 1 == pOne->col && player.row == pOne->row;
	}

	// Switch and move based on direction chosen
	switch (d) {
	case Board::UP:
		if (up && gb->board[player.row - 1][player.col]->up) {
			player.row -= 2;
			return true;
		}
		if (gb->board[player.row][player.col]->up && !up) {
			player.row -= 1;
			return true;
		}
		return false;
	case Board::DOWN:
		if (down && gb->board[player.row + 1][player.col]->down) {
			player.row += 2;
			return true;
		}
		if (gb->board[player.row][player.col]->down && !down) {
			player.row += 1;
			return true;
		}
		return false;
	case Board::LEFT:
		if (left && gb->board[player.row][player.col - 1]->left) {
			player.col -= 2;
			return true;
		}
		if (gb->board[player.row][player.col]->left && !left) {
			player.col -= 1;
			return true;
		}
		return false;
	case Board::RIGHT:
		if (right && gb->board[player.row][player.col + 1]->right) {
			player.col += 2;
			return true;
		}
		if (gb->board[player.row][player.col]->right && !right) {
			player.col += 1;
			return true;
		}
		return false;
	case Board::UPLEFT:
		if (up && !gb->board[player.row - 1][player.col]->up) {
			player.row -= 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::UPRIGHT:
		if (up && !gb->board[player.row - 1][player.col]->up) {
			player.row -= 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::DOWNLEFT:
		if (down && !gb->board[player.row + 1][player.col]->down) {
			player.row += 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::DOWNRIGHT:
		if (down && !gb->board[player.row + 1][player.col]->down) {
			player.row += 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::LEFTUP:
		if (left && !gb->board[player.row][player.col - 1]->left) {
			player.row -= 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::LEFTDOWN:
		if (left && !gb->board[player.row][player.col - 1]->left) {
			player.row += 1;
			player.col -= 1;
			return true;
		}
		return false;
	case Board::RIGHTUP:
		if (right && !gb->board[player.row][player.col + 1]->right) {
			player.row -= 1;
			player.col += 1;
			return true;
		}
		return false;
	case Board::RIGHTDOWN:
		if (right && !gb->board[player.row][player.col + 1]->right) {
			player.row += 1;
			player.col += 1;
			return true;
		}
		return false;
	default:
		return false;
	}
}

// Post-Condition: checks if a player is blocked from goal or not
// Returns: true if not blocked from goal false otherwise
bool Board::checkNotBlocked() {
	queue<Square*> q;
	bool check = false;
	// check player 1
	gb->board[pOne->row][pOne->col]->seen = true;
	q.push(gb->board[pOne->row][pOne->col]);	
	
	// Use breadth first to make sure we can still finish the game
	while (!q.empty()) {
		Square * temp = q.front();
		q.pop();
		if (temp->row == 8) {
			check = true;
			break;
		}
		if (temp->up && !gb->board[temp->row - 1][temp->col]->seen) {
			gb->board[temp->row - 1][temp->col]->seen = true;
			q.push(gb->board[temp->row - 1][temp->col]);
		}
		if (temp->down && !gb->board[temp->row + 1][temp->col]->seen) {
			gb->board[temp->row + 1][temp->col]->seen = true;
			q.push(gb->board[temp->row + 1][temp->col]);
		}
		if (temp->left && !gb->board[temp->row][temp->col - 1]->seen) {
			gb->board[temp->row][temp->col - 1]->seen = true;
			q.push(gb->board[temp->row][temp->col - 1]);
		}
		if (temp->right && !gb->board[temp->row][temp->col + 1]->seen) {
			gb->board[temp->row][temp->col + 1]->seen = true;
			q.push(gb->board[temp->row][temp->col + 1]);
		}
	}

	// empty the queue
	while (!q.empty())
		q.pop();

	// reset all the seen booleans
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			gb->board[row][col]->seen = false;

	// reset check
	if (!check)
		return check;
	check = false;


	// check player 2
	q.push(gb->board[pTwo->row][pTwo->col]);
	gb->board[pTwo->row][pTwo->col]->seen = true;
	
	// User breadth first to check if player 2 is blocked
	while (!q.empty()) {
		Square * temp = q.front();
		q.pop();
		if (temp->row == 0) {
			check = true;
			break;
		}
		if (temp->up && !gb->board[temp->row - 1][temp->col]->seen) {
			gb->board[temp->row - 1][temp->col]->seen = true;
			q.push(gb->board[temp->row - 1][temp->col]);
		}
		if (temp->down && !gb->board[temp->row + 1][temp->col]->seen) {
			gb->board[temp->row + 1][temp->col]->seen = true;
			q.push(gb->board[temp->row + 1][temp->col]);
		}
		if (temp->left && !gb->board[temp->row][temp->col - 1]->seen) {
			gb->board[temp->row][temp->col - 1]->seen = true;
			q.push(gb->board[temp->row][temp->col - 1]);
		}
		if (temp->right && !gb->board[temp->row][temp->col + 1]->seen) {
			gb->board[temp->row][temp->col + 1]->seen = true;
			q.push(gb->board[temp->row][temp->col + 1]);
		}
	}

	// reset all the seens to false
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			gb->board[row][col]->seen = false;

	// return the results
	return check;
}