#include "QuorAI.h"

const int CURVE = 100;

// CONSTRUCTOR
QuorAI::QuorAI(int player) {
    this->player = player;
	firstTurn = true;
	dbc = new DBConnection();
    srand(time(NULL));
}

// Parameters: board - the most recent board configuration
// Post-Condition: set the mostRecentBoard field
void QuorAI::setMostRecentBoard(string mrb) {
    wasValid = mostRecentBoard.compare(mrb) != 0;
	if (firstTurn == true) {
		prevBoard = mrb;
		firstTurn = false;
		wasValid = false;
	} else
		prevBoard = mostRecentBoard;
    mostRecentBoard = mrb;
}

// Parameters: i - the int to convert to a string
// Post-Condition: turns an integer to a string
// Returns: the int as a string
string QuorAI::intToString(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

// Returns: A random pawn move.
string QuorAI::makeRandomPawnMove() {
    string moves[12] = {
        "up", "down", "left", "right", "upleft", "upright", "downleft", 
        "downright", "leftup", "leftdown", "rightup", "rightdown"};

    return "pawn " + moves[rand() % 12];
}

// Returns: A random wall move;
string QuorAI::makeRandomWall() {
    int row = rand() % 8;
    int col = rand() % 8;
    
    string dir = "";
    
    if (rand() % 2 == 1) {
        dir = "h";
    } else {
        dir = "v";
    }

    return "wall " + dir + " " + intToString(row) + " " + intToString(col);
}

// Returns: the next move the agent will make.
string QuorAI::getNextMove() {
  // was our last move was valid?
	if (wasValid) {
	    rememberPrevState();
            countPrevMoves = 0;	
   	}
	string move = makeIntelligentMove();
	prevMoves[countPrevMoves] = move;
    	countPrevMoves++;

	return move;
}

// Returns: A random move; either a pawn move or a wall placement.
string QuorAI::makeRandomMove() {
    if (rand() % 10 == 0)
	return makeRandomWall();        
    return makeRandomPawnMove();
}
 
// Returns: Next move either a pawn move or a wall move
string QuorAI::getRandomMove() {
    
     
    bool alreadyTried = false;

    string move;

    move = makeRandomMove();

    do {
        for (int i = 0; i < countPrevMoves; i++) {
            alreadyTried = move.compare(prevMoves[i]) == 0;
            if (alreadyTried) {
                move = makeRandomMove();
                break;
            }
        }
    } while (alreadyTried);

    return move;
}

// Remember the agent's previous state
// Postconditions: requests the game state (board configuration) to be stored 
//                 in the database
void QuorAI::rememberPrevState() {
	if (countPrevMoves < 1)
		return;
	string move = prevMoves[countPrevMoves - 1];
	size_t hash = hashString(prevBoard);	
	dbc->addGameState(player, prevBoard, move, hash);
}

// Notifies the database connector who won
// Parameters: winner - the winner of the game.
// Postcondition: ends the game.
void QuorAI::giveWinner(int winner) {
	dbc->endGame(player, winner);
	delete dbc;
}

// Hashes the string of a given board configuration
// Parameters: str - the board configuration needing to be hashed
// Returns: the value after the hash
unsigned int QuorAI::hashString(const std::string& str) {
   unsigned int hash = 1315423911;
   for(std::size_t i = 0; i < str.length(); i++)
      hash ^= ((hash << 5) + str[i] + (hash >> 2));
   return hash;
}

// Determines a move intelligently by communicating to the database connector
// Returns: the next move to make
string QuorAI::makeIntelligentMove() {
	if (abs(rand() % 100 + 1) > CURVE)
	    return getRandomMove();

	string move = dbc->getState(hashString(mostRecentBoard), mostRecentBoard, player);
	
	if (move.compare("null") == 0)
	    return getRandomMove();

	cout << "Player: " << player <<" Move: " << move << endl;

	return move;
}








