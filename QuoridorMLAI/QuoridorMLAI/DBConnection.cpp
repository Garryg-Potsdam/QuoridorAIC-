#include "DBConnection.h"

// Creates a connection to the database and allows for various calls to the database.
DBConnection::DBConnection() {
  
  // Set at counter to keep track of the number of moves made
	counter = 0;
  
	srand(time(NULL));
	
  // template query to append to when a game takes place.
  queries = "INSERT INTO states(playerNumber, stateGameID, stringRepresentation, nextMove, boardHash) VALUES ";	
    try {
        /* Create a connection */

        driver = get_driver_instance();

        con = driver->connect("tcp://quordb.c42xpoddmdpg.us-west-2.rds.amazonaws.com", "root", "root1234");

        /* Connect to the MySQL quordb database */

        con->setSchema("quordb");

    } catch (sql::SQLException & e) {

        cout << "# ERR: SQLException in " << __FILE__;

        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;

        cout << "# ERR: " << e.what();

        cout << " (MySQL error code: " << e.getErrorCode();

        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

    }
	gameStart();
}

//  Starts the game's connection to the database.
//  Postcondition: Inserts a new game row into the database with a winner value as -1.
void DBConnection::gameStart() {
	sql::ResultSet * result;	
	result = con->prepareStatement("INSERT INTO games (isWinner) VALUES (-1);")->executeQuery();
	result = con->prepareStatement("SELECT LAST_INSERT_ID();")->executeQuery();
	result->first();
	gameID = result->getInt(1);
	cout << "GameID: " << gameID << endl;
}


string * DBConnection::getGameStates() {
    return NULL;
}

// Parameters: i - int to turn to string
// Returns: string of the passed in int
std::string DBConnection::intToString(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

// Parameters: d - double to turn to string
// Returns: string of the passed in int
std::string DBConnection::dblToString(double d) {
    std::stringstream ss;
    ss << d;
    return ss.str();
}

// Adds a board configuration (state) to the game
// Parameters:
//   player - the player number
//   prevBoard - the previous board played
//   move - the move made by the player to get to prevBoard
//   hash - the hash value of the board configuration (state)
// Postcondition: Adds these values to a query string and increments a counter for the number of moves.
void DBConnection::addGameState(int player, string prevBoard, string move, int hash) {	
	queries += "(" + intToString(player) + ", " + intToString(gameID) + ", '" + prevBoard + "', '" + move + "', " + intToString(hash) + "),";
	counter++;
}

// Ends the game
// Parameters:
//   player - the player number of the agent
//   winner - the winner of the game
// Postcondition: updates the game information (including all states) to the 
//                database ONLY IF the agent won the game. Also deletes the 
//                database connection.
void DBConnection::endGame(int player, int winner) {
	if (player == winner) {
		queries = queries.substr(0, queries.length() - 1) + ";";
		con->prepareStatement(queries)->executeQuery();
		con->prepareStatement("UPDATE games SET isWinner=" + intToString(winner) + " WHERE gamesID=" + intToString(gameID) + ";")->executeQuery();
		updateWeights();
	}
	
    delete con;
}

// Updates the game's weight (the fewer the moves the higher the weight)
// Postcondition: updates the game's weight in the database to reflect the 
//                expected value (strength of this game to help reach a lower 
//                winning move count).
void DBConnection::updateWeights() {
	double weight = 1 / (double) counter;
	con->prepareStatement("UPDATE states SET weight=" + dblToString(weight) + " WHERE stateGameID=" + intToString(gameID) + ";")->executeQuery();
}

// A highly coupled method that determines the next state the agent should make 
// based on the agent's current board configuration.
// Parameters:
//  hash - the value after hashing the board configuration string
//  currState - the current state the agent is in (board configuration)
//  player - the agent's player number
// Returns: -1 if not moves were found, the next board coniguration of the next 
//          move to make.
string DBConnection::getState(int hash, string currState, int player) {
	// position 0 game id
	// position 1 state id
	vector<int> gameState;
	gameState.push_back(-1);
	gameState.push_back(-1);
	
  // Grab all of the string representations with the matching hash.
	sql::ResultSet * res;
	res = con->prepareStatement("SELECT stringRepresentation, weight, nextMove FROM states, games WHERE games.gamesID = states.stateGameID AND games.isWinner=" 
                                    + intToString(player) + " AND states.boardHash=" + intToString(hash) + ";")->executeQuery();
	
	vector<double> weights;
	vector<string> nextMoves;	
	
  // weed out collisions by ensuring each item in the subset of board 
  // configurations are equal to the agent's current board configuration
	while(res->next()) {
		int i = 0;
		string board = res->getString("stringRepresentation");
		if (currState.compare(board) == 0) {
			weights.push_back(res->getDouble("weight"));
			nextMoves.push_back(res->getString("nextMove"));
		}
		i++;
	}
	
  // Randomly choose the next move based on game's weight compared to the 
  // result of dividing two random doubles.
	if(weights.size() > 0) {
		int index = 0;
		int size = weights.size();
		while(weights[index] < (double)abs(rand()) / (double)abs(rand())) {			
			index++;
			index %= size;
		}
		return nextMoves[index];		
	};
  
	return "null";
}
