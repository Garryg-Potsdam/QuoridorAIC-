#include "Board.h"


int humanPlayer = 0;
int ai = 1;
Board board;

void startGame();
void AIMove();
void humanMove();

int main() {	
	startGame();
	cout << board.PrintBoard() << endl;
	while (!board.checkWinner()) {		
		if (humanPlayer == 1)
			humanMove();
		else
			AIMove();
		cout << board.PrintBoard() << endl;		
		if (board.checkWinner())
			break;
		if (humanPlayer == 2)
			humanMove();
		else
			AIMove();
		cout << board.PrintBoard() << endl;		
	};	
	cout << "The winner is " << board.getWinner() << "!" << endl;	
	int x;
	cin >> x;
	return 0;
}

void AIPlaceWalls() {
	int row = -1;
	int col = -1;
	string direction = "";
	string message1 = "AI Wall: v - for Vertical |. /n h - for Horizontal __. ";
	cout << message1;
	
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
			message1 = "Invalid wall try again. " + message1;
			row = -1;
			col = -1;
			direction = "";
		}
	}
	cout << "AI Wall: The wall was successfully places at [(" << row << ", " << col << "), " << direction << "]" << endl;
}

void HumanPlaceWalls() {
	int row = -1;
	int col = -1;
	string direction = "";
	string message1 = "Human Wall: v - for Vertical |. /n h - for Horizontal __. ";
	

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
		success = board.placeWalls(humanPlayer, row, col, direction);
		if (!success) {
			message1 = "Invalid wall try again. " + message1;
			row = -1;
			col = -1;
			direction = "";
		}
	}
	cout << "Human Wall: The wall was successfully places at [(" << row << ", " << col << "), " << direction << "]" << endl;
}

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
			message1 = "Invalid move try again. " + message1;
			direction = "";
		}
	}
	cout << "Pawn was successfully moved." << endl;
}


void HumanMovePawn() {	
	bool success = false;
	string direction = "";
	string message1 = "Pick a direction human. (up(left,right), down(left,right), left(up, down), right(up, down)): ";
	while (!success) {
		while (direction.compare("up") != 0 && direction.compare("down") != 0 && direction.compare("left") != 0 && direction.compare("right") != 0 &&
			direction.compare("upleft") != 0 && direction.compare("upright") != 0 && direction.compare("downleft") != 0 && direction.compare("downright") != 0 &&
			direction.compare("leftup") != 0 && direction.compare("leftdown") != 0 && direction.compare("rightup") != 0 && direction.compare("rightdown") != 0) {
			cout << message1;
			cin >> direction;
		}
		success = board.movePawn(humanPlayer, direction);
		if (!success) {
			message1 = "Invalid move try again. " + message1;
			direction = "";
		}
	}
	cout << "Pawn was successfully moved." << endl;
}

void AIMove() {
	bool success = false;
	string moveType = "";
	string message1 = "Wall move or pawn move? ";
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << message1;
		cin >> moveType;
	}
	if (moveType.compare("pawn") == 0)
		AIMovePawn();
	else
		AIPlaceWalls();

}

void humanMove() {
	bool success = false;
	string moveType = "";
	string message1 = "Wall move or pawn move? ";
	while (moveType.compare("wall") != 0 && moveType.compare("pawn") != 0) {
		cout << message1;
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