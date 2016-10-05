#include "Board.h"

// Keep trach of whos turn it is
int humanPlayer = 0;
int ai = 1;

// Intance of the board
Board board;

// Runs through the game start up process
void startGame();

// Requests a move from the AI
void AIMove();

// Requests a pawn move from the AI
void AIMovePawn();

// Requests a wall move from the AI
void AIPlaceWalls();

// Requests type of move player wants to perform
void humanMove();

// requests what pawn move the human player wants
void HumanMovePawn();

// requests the wall that the human play wants to play
void HumanPlaceWalls();


// Main client function for game of Quoridor
int main() {

	// Start the game
	startGame();

	// TODO: add initial board delivery to AI

	// Print the initial board for the human player
	cout << board.PrintBoard() << endl;

	// while there is no winner keep playing
	while (!board.checkWinner()) {
		// basic move checks
		if (humanPlayer == 1)
			humanMove();
		else
			AIMove();
		// someone moved print the board
		cout << board.PrintBoard() << endl;		

		// basic move check
		if (board.checkWinner())
			break;
		if (humanPlayer == 2)
			humanMove();
		else
			AIMove();

		// someone moved print the board again
		cout << board.PrintBoard() << endl;		
	};	

	// TODO: add connections to AI for delivering information

	// tell the human who won
	cout << "The winner is " << board.getWinner() << "!" << endl;	
	int x;
	cin >> x;
	return 0;
}


// Runs through the game start up process
void startGame() {

	// Ask the human player what position they want
	while (humanPlayer != 1 && humanPlayer != 2) {
		cout << "Hello human. Will you be player 1 or player 2? ";
		cin >> humanPlayer;
	}

	// set the AI position
	if (humanPlayer == 1)
		ai = 2;

	// Confirm command
	cout << "Great human! You are player " << humanPlayer << "!\n";
}

// Requests type of move player wants to perform
void humanMove() {

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
		HumanMovePawn();
	else
		HumanPlaceWalls();
}

// requests what pawn move the human player wants
void HumanMovePawn() {

	// successful move boolean
	bool success = false;
	// store move direction string and request message
	string direction = "";
	string message1 = "Pick a direction human. (up(left,right), down(left,right), left(up, down), right(up, down)): ";

	// checks if move choice is valid
	while (!success) {
		while (direction.compare("up") != 0 && direction.compare("down") != 0 && direction.compare("left") != 0 && direction.compare("right") != 0 &&
			direction.compare("upleft") != 0 && direction.compare("upright") != 0 && direction.compare("downleft") != 0 && direction.compare("downright") != 0 &&
			direction.compare("leftup") != 0 && direction.compare("leftdown") != 0 && direction.compare("rightup") != 0 && direction.compare("rightdown") != 0) {
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

// requests the wall that the human play wants to play
void HumanPlaceWalls() {

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
				cout << "Pick a row from (0 - 8): ";
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
				cout << "Pick a col from (0 - 8): ";
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

// !!!!!ATTENTION!!!!!
// NOTE: all the following functions will be drastically changed when AI is implemented

// request move from the ai
void AIMove() {
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
		AIMovePawn();
	else
		AIPlaceWalls();
}

// Requests a pawn move from the AI
void AIMovePawn() {

	bool success = false;
	string message1 = "AI is thinkin... ";
	string direction = "";
	while (!success) {
		while (direction.compare("up") != 0 && direction.compare("down") != 0 && direction.compare("left") != 0 && direction.compare("right") != 0 &&
			direction.compare("upleft") != 0 && direction.compare("upright") != 0 && direction.compare("downleft") != 0 && direction.compare("downright") != 0 &&
			direction.compare("leftup") != 0 && direction.compare("leftdown") != 0 && direction.compare("rightup") != 0 && direction.compare("rightdown") != 0) {
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
void AIPlaceWalls() {
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
				cout << "Pick a row from (0 - 8): ";
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
				cout << "Pick a col from (0 - 8): ";
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