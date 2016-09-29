#include "Board.h"


int humanPlayer = 0;
int ai = 1;
Board board;

void startGame();
void AIMove();
void humanMove();

int main() {	
	startGame();
	bool done = false;
	cout << board.PrintBoard() << endl;
	while (!done) {		
		if (humanPlayer == 1)
			humanMove();
		else
			AIMove();
		cout << board.PrintBoard() << endl;
		if (humanPlayer == 2)
			humanMove();
		else
			AIMove();
		cout << board.PrintBoard() << endl;
	};	
	
	return 0;
}

void AIPlaceWalls() {
	int row = -1;
	int col = -1;
	string direction = "";
	
	cout << "v - for Vertical |. /n h - for Horizontal __. ";
	while (direction.compare("h") != 0 && direction.compare("v") != 0)
		cin >> direction;
	if (direction.compare("h") == 0) {		
		while (row < 0 || row > 8) {
			cout << "Pick a row from (0 - 8): ";
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
			cout << "Pick a col from (0 - 8): ";
			cin >> col;
		}
	}	
	cout << board.placeWalls(ai, row, col, direction) << endl;
}

void HumanPlaceWalls() {
	int row = -1;
	int col = -1;
	string direction = "";

	cout << "v - for Vertical |. /n h - for Horizontal __. ";
	while (direction.compare("h") != 0 && direction.compare("v") != 0)
		cin >> direction;
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
	cout << board.placeWalls(ai, row, col, direction) << endl;

}

void AIMovePawn() {
	cout << "AI is thinkin... ";
	string direction = "";
	cin >> direction;
	while (direction.compare("up") != 0 && direction.compare("down") != 0 && direction.compare("left") != 0 && direction.compare("right") != 0)
		cin >> direction;
	cout << board.movePawn(ai, direction) << endl;
}


void HumanMovePawn() {	
	string direction = "";
	cin >> direction;
	while (direction.compare("up") != 0 && direction.compare("down") != 0 && direction.compare("left") != 0 && direction.compare("right") != 0) {
		cout << "Pick a direction human. (up, down, left, right): ";
		cin >> direction;
	}
	cout << board.movePawn(humanPlayer, direction) << endl;
}

void AIMove() {
	string moveType = "";	
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << "Wall move or pawn move? ";
		cin >> moveType;
	}
	if (moveType.compare("pawn") == 0)
		AIMovePawn();
	else
		AIPlaceWalls();
}

void humanMove() {
	string moveType = "";	
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << "Wall move or pawn move? ";
		cin >> moveType;
	}
	if (moveType.compare("pawn") == 0)
		HumanMovePawn();
	else
		HumanPlaceWalls();
}

void startGame() {	
	while (humanPlayer != 1 && humanPlayer != 2) {
		cout << "Hello human. Will you be player 1 or player 2? ";
		cin >> humanPlayer;
	}
	if (humanPlayer == 1)
		ai = 2;
	cout << "Great human! You are player " << humanPlayer << "!\n";
}
