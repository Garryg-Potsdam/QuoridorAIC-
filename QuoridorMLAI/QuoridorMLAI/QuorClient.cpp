#include "Board.h"
#include "QuorAI.h"

// Runs through the game start up process
int startGame();

// Returns: the human player number
int getHumanSpot();

// Requests type of move player wants to perform
void humanMove(Board &board, int humanPlayer);

// requests what pawn move the human player wants
bool HumanMovePawn(Board &board, int humanPlayer);

// requests the wall that the human play wants to play
bool HumanPlaceWalls(Board &board, int humanPlayer);

// Parameters: move - the move string
// Returns: true if it is a valid move string false otherwise
bool contains(string move);

// Requests a move from the AI
void AIMove(QuorAI &ai, Board &board, int humanPlayer);

// Requests a pawn move from the AI
bool AIMovePawn(Board &board, int ai, string move);

// Requests a wall move from the AI
bool AIPlaceWalls(Board &board, int ai, string move);

QuorAI *aiOne, *aiTwo;

// Main client function for game of Quoridor
int main() {

	// Intance of the board
	Board * board;
	board = new Board;
	
	// Keep trach of whos turn it is
	int humanPlayer = startGame();
    
    aiOne->setMostRecentBoard(board->toString());
    
	// Print the initial board for the human player
	//cout << board->toString() << endl;

    if (humanPlayer != -1) {
    	// while there is no winner keep playing
	    while (!board->checkWinner()) {
		    // basic move checks
		    if (humanPlayer == 1)
			    humanMove(*board, humanPlayer);
		    else
			    AIMove(*aiOne, *board, 1);
    		// someone moved print the board
	    	//cout << board->toString() << endl;		

		    // basic move check
    		if (board->checkWinner())
	    		break;

		    if (humanPlayer == 2)
			    humanMove(*board, humanPlayer);
    		else
	    		AIMove(*aiOne, *board, 2);
    
	    	// someone moved print the board again
		    //cout << board->toString() << endl;		
	    };
    } else {	
		aiTwo->setMostRecentBoard(board->toString());
        while (!board->checkWinner()) {
            // ai one moves
            AIMove(*aiOne, *board, 1);
            // update the printed board
            //cout << board->toString() << endl;

            // check if ai one won
            if (board->checkWinner())
                break;

            // ai two moves
            AIMove(*aiTwo, *board, 2);
            // update the printed board
            //cout << board->toString() << endl;
        }
		aiTwo->giveWinner(board->getWinner());
    }

	// tell what player won
	//cout << "The winner is Player " << board->getWinner() << "!" << endl;
	cout << board->toString() << endl;
	aiOne->giveWinner(board->getWinner());
	delete board;

	return 0;
}

// Runs through the game start up process
int startGame() {
	int amountOfAIs = 2;
	// Ask the human player what position they want
	//while (amountOfAIs != 1 && amountOfAIs != 2) {
	//	cout << "Are you playing 1(Yes) or 2(No): ";
	//	cin >> amountOfAIs;
	//}
    if (amountOfAIs == 1) {
        // get the human player
        int human = getHumanSpot();

        // set ai player
        if (human == 1)
            aiOne = new QuorAI(2);
        else
            aiOne = new QuorAI(1);

        // announce human player
	    cout << "Great human! You are player " << human << "!\n";

        return human;
    } else { // no human player set AIs
        aiOne = new QuorAI(1);
        aiTwo = new QuorAI(2);
    }

	// if not human player return -1
	return -1;
}

// Returns: the human player number
int getHumanSpot() {
    int playerNum = 0;
    while (playerNum != 1 && playerNum != 2) {
        cout << "What player do you want to be (1 or 2): ";
        cin >> playerNum;
    }
    return playerNum; 
}

// Parameters:       board - the board to play on
//		humanPlayer - the position of the human player
// Requests type of move player wants to perform
void humanMove(Board &board, int humanPlayer) {
    bool success = false;
    while (!success) {
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
		    success = HumanMovePawn(board, humanPlayer);            
	    else
	    	success = HumanPlaceWalls(board, humanPlayer);
    }
}

// Parameters:       board - the board to play on
//			   humanPlayer - the position of the human player
// requests what pawn move the human player wants
bool HumanMovePawn(Board &board, int humanPlayer) {

	// store move direction string and request message
	string direction = "";
	string message1 = "Pick a direction human. (up(left, right), down(left, right), left(up, down), right(up, down)): ";	

	// checks if move choice is valid	
	while (!contains(direction)) {
		cout << message1;
		cin >> direction;
	}
    bool success = board.movePawn(humanPlayer, direction);

	// announce to player the results
    if (success)
        cout << "Pawn was successfully moved." << endl;
    else
        cout << "Invalid pawn move" << endl;
    return success;
}

// Parameters:       board - the board to play on
//			   humanPlayer - the position of the human player
// requests the wall that the human play wants to play
bool HumanPlaceWalls(Board &board, int humanPlayer) {

	// row and col and direction(Vertical/Horizontal) placements storage for wall move
	int row = -1;
	int col = -1;
	string direction = "";
	// Wall move request message
	string message1 = "Human Wall: v - for Vertical |. /n h - for Horizontal __. ";

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
    
    bool success = board.placeWalls(humanPlayer, row, col, direction);
	if (!success) 
		cout << "Invalid wall try again." << endl;
	else
	    cout << "Human Wall: The wall was successfully placed at [(" << row << ", " << col << "), " << direction << "]" << endl;
    return success;
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

// Parameters:    &ai - the ai whose move it is
//             &board - the gameboard
//              aiNum - the ais number
// Post-Condition: commuicates AI move
void AIMove(QuorAI &ai, Board &board, int aiNum) {
    bool success = false;
    while (!success) {
		ai.setMostRecentBoard(board.toString());
        string currMove = ai.getNextMove();
    
        string moveType = currMove.substr(0, 4);
        currMove.erase(0, 5);
		if (moveType.compare("pawn") == 0) {
	    	success = AIMovePawn(board, aiNum, currMove);
        } else {
	    	success = AIPlaceWalls(board, aiNum, currMove);
        }
    }
}

// Requests a pawn move from the AI
bool AIMovePawn(Board &board, int ai, string move) {
    return board.movePawn(ai, move);    
}


// Requests a wall move from the AI
// h 3 4
bool AIPlaceWalls(Board &board, int ai, string move) {
    string direction = move.substr(0, 1);
    move.erase(0, 2);
	int row = board.stringToInt(move.substr(0, 1));
    move.erase(0, 2);
	int col = board.stringToInt(move);

    // if succesful move print
    bool success = board.placeWalls(ai, row, col, direction);
    //if (success)
    //    cout << "AI Wall: The wall was successfully placed at [(" << row << ", " << col << "), " << direction << "]" << endl;
    return success;
}
