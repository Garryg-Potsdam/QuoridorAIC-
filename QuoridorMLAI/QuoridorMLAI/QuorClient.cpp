#include "Board.h"


// Runs through the game start up process
int startGame();

// Requests type of move player wants to perform
void humanMove(Board &board, int humanPlayer);

// requests what pawn move the human player wants
void HumanMovePawn(Board &board, int humanPlayer);

// requests the wall that the human play wants to play
void HumanPlaceWalls(Board &board, int humanPlayer);

// Parameters: move - the move string
// Returns: true if it is a valid move string false otherwise
bool contains(string move);

// Requests a move from the AI
void AIMove(Board &board, int humanPlayer);

// Requests a pawn move from the AI
void AIMovePawn(Board &board, int ai);

// Requests a wall move from the AI
void AIPlaceWalls(Board &board, int ai);


// Main client function for game of Quoridor
int main() {

	

	// Intance of the board
	Board * board;
	board = new Board;
	
	// Keep trach of whos turn it is
	int humanPlayer = startGame();

	// TODO: add initial board delivery to AI

	// Print the initial board for the human player
	cout << board->toString() << endl;

	// while there is no winner keep playing
	while (!board->checkWinner()) {
		// basic move checks
		if (humanPlayer == 1)
			humanMove(*board, humanPlayer);
		else
			AIMove(*board, humanPlayer);
		// someone moved print the board
		cout << board->toString() << endl;		

		// basic move check
		if (board->checkWinner())
			break;
		if (humanPlayer == 2)
			humanMove(*board, humanPlayer);
		else
			AIMove(*board, humanPlayer);

		// someone moved print the board again
		cout << board->toString() << endl;		
	};	

	// TODO: add connections to AI for delivering information

	// tell the human who won
	cout << "The winner is " << board->getWinner() << "!" << endl;	
	
	delete board;

	return 0;
}


// Runs through the game start up process
int startGame() {
	int humanPlayer = 0;
	// Ask the human player what position they want
	while (humanPlayer != 1 && humanPlayer != 2) {
		cout << "Hello human. Will you be player 1 or player 2? ";
		cin >> humanPlayer;
	}

	// Confirm command
	cout << "Great human! You are player " << humanPlayer << "!\n";
	return humanPlayer;
}

// Parameters:       board - the board to play on
//			   humanPlayer - the position of the human player
// Requests type of move player wants to perform
void humanMove(Board &board, int humanPlayer) {

	// store move variable and request string
	string moveType = "";
	string message1 = "Wall move or pawn move? ";

	// detemine move type
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << message1;
		cin >> moveType;
	}

	// call correct move function based on move type
	if (moveType.compare("pawn") == 0)
		HumanMovePawn(board, humanPlayer);
	else
		HumanPlaceWalls(board, humanPlayer);
}

// Parameters:       board - the board to play on
//			   humanPlayer - the position of the human player
// requests what pawn move the human player wants
void HumanMovePawn(Board &board, int humanPlayer) {

	// successful move boolean
	bool success = false;
	// store move direction string and request message
	string direction = "";
	string message1 = "Pick a direction human. (up(left, right), down(left, right), left(up, down), right(up, down)): ";	

	// checks if move choice is valid
	while (!success) {
		while (!contains(direction)) {
			cout << message1;
			cin >> direction;
		}
		// set success to true or false if false try again
		success = board.movePawn(humanPlayer, direction);
		if (!success) {
			cout << "Invalid move try again. " << endl;
			direction = "";
		}
	}

	// announce to player the results
	cout << "Pawn was successfully moved." << endl;
}

// Parameters:       board - the board to play on
//			   humanPlayer - the position of the human player
// requests the wall that the human play wants to play
void HumanPlaceWalls(Board &board, int humanPlayer) {

	// row and col and direction(Vertical/Horizontal) placements storage for wall move
	int row = -1;
	int col = -1;
	string direction = "";
	// Wall move request message
	string message1 = "Human Wall: v - for Vertical |. /n h - for Horizontal __. ";
	
	// successful wall placement boolean
	bool success = false;

	// This checks for a valid wall arrangement to avoid having to make a call to the board
	while (!success) {
		while (direction.compare("h") != 0 && direction.compare("v") != 0) {
			cout << message1;
			cin >> direction;
		}
		if (direction.compare("h") == 0) {
			while (row < 0 || row > 8) {
				cout << "Pick a row from (0 - 7): ";
				cin >> row;
			}
			while (col < 0 || col > 7) {
				cout << "Pick a col from (0 - 7): ";
				cin >> col;
			}
		} else {
			while (row < 0 || row > 7) {
				cout << "Pick a row from (0 - 7): ";
				cin >> row;
			}
			while (col < 0 || col > 8) {
				cout << "Pick a col from (0 - 7): ";
				cin >> col;
			}
		}

		// TODO: allow to cancel a specific move type to try something else

		// while success is false keep asking
		success = board.placeWalls(humanPlayer, row, col, direction);
		if (!success) {
			cout << "Invalid wall try again." << endl;
			row = -1;
			col = -1;
			direction = "";
		}
	}

	// Confirm successful wall placement to human player
	cout << "Human Wall: The wall was successfully placed at [(" << row << ", " << col << "), " << direction << "]" << endl;
}

// Parameters: move - the move string
// Returns: true if it is a valid move string false otherwise
bool contains(string move) {
	string moves[12] = { "up", "down", "left", "right", "upleft", "upright", "downleft", "downright", "leftup", "leftdown", "rightup", "rightdown" };
	for (int i = 0; i < 12; i++) {
		if (move.compare(moves[i]) == 0)
			return true;
	}
	return false;
}

// !!!!!ATTENTION!!!!!
// NOTE: all the following functions will be drastically changed when AI is implemented

// request move from the ai
void AIMove(Board &board, int humanPlayer) {
	// Determine move type
	string moveType = "";
	string message1 = "Wall move or pawn move? ";

	// gather and store the move type
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << message1;
		cin >> moveType;
	}

	// perform move type call
	if (moveType.compare("pawn") == 0)
		AIMovePawn(board, humanPlayer);
	else
		AIPlaceWalls(board, humanPlayer);
}

// Requests a pawn move from the AI
void AIMovePawn(Board &board, int humanPlayer) {
	int ai = 1;
	if (humanPlayer == 1)
		ai = 2;

	bool success = false;
	string message1 = "AI is thinkin... ";
	string direction = "";
	while (!success) {
		while (!contains(direction)) {
			cout << message1;
			cin >> direction;
		}
		cout << direction;
		success = board.movePawn(ai, direction);
		if (!success) {
			cout << "Invalid move try again. " << endl;
			direction = "";
		}
	}
	cout << "Pawn was successfully moved." << endl;
}


// Requests a wall move from the AI
void AIPlaceWalls(Board &board, int ai) {
	int row = -1;
	int col = -1;
	string direction = "";
	string message1 = "AI Wall: v - for Vertical |. /n h - for Horizontal __. ";

	bool success = false;
	while (!success) {
		while (direction.compare("h") != 0 && direction.compare("v") != 0) {
			cout << message1;
			cin >> direction;
		}
		if (direction.compare("h") == 0) {
			while (row < 0 || row > 8) {
				cout << "Pick a row from (0 - 7): ";
				cin >> row;
			}
			while (col < 0 || col > 7) {
				cout << "Pick a col from (0 - 7): ";
				cin >> col;
			}
		}
		else {
			while (row < 0 || row > 7) {
				cout << "Pick a row from (0 - 7): ";
				cin >> row;
			}
			while (col < 0 || col > 8) {
				cout << "Pick a col from (0 - 7): ";
				cin >> col;
			}
		}
		success = board.placeWalls(ai, row, col, direction);
		if (!success) {
			cout << "Invalid wall try again." << endl;
			row = -1;
			col = -1;
			direction = "";
		}
	}
	cout << "AI Wall: The wall was successfully places at [(" << row << ", " << col << "), " << direction << "]" << endl;
}