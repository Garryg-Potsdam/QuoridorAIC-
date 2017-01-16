/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>

/*
Include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class DBConnection {

public:
    // Creates a connection to the database and allows for various calls to the database.
    DBConnection();
    
    // Adds a board configuration (state) to the game
    // Parameters:
    //   player - the player number
    //   prevBoard - the previous board played
    //   move - the move made by the player to get to prevBoard
    //   hash - the hash value of the board configuration (state)
    // Postcondition: Adds these values to a query string and increments a counter for the number of moves.
    void addGameState(int player, string prevBoard, string move, int hash);
    
    
    string * getGameStates();
    
    //  Starts the game's connection to the database.
    //  Postcondition: Inserts a new game row into the database with a winner value as -1.
    void gameStart();
    
    // Ends the game
    // Parameters:
    //   player - the player number of the agent
    //   winner - the winner of the game
    // Postcondition: updates the game information (including all states) to the 
    //                database ONLY IF the agent won the game. Also deletes the 
    //                database connection.
    void endGame(int player, int winner);
    
    // A highly coupled method that determines the next state the agent should make 
    // based on the agent's current board configuration.
    // Parameters:
    //  hash - the value after hashing the board configuration string
    //  currState - the current state the agent is in (board configuration)
    //  player - the agent's player number
    // Returns: -1 if not moves were found, the next board coniguration of the next 
    //          move to make.
    string getState(int hash, string currState, int player);
    
    
private:
	int gameID;
  // template query to append to when a game takes place.
	string queries;
  // MYSQL driver
  sql::Driver * driver;
  // MYSQL connection
  sql::Connection * con;
  int counter;
    

	// Parameters: i - int to turn to string
	// Returns: string of the passed in int
	std::string intToString(int i);
	
	// Parameters: d - double to turn to string
	// Returns: string of the passed in int
	std::string dblToString(double d);
	
  // Updates the game's weight (the fewer the moves the higher the weight)
  // Postcondition: updates the game's weight in the database to reflect the 
  //                expected value (strength of this game to help reach a lower 
  //                winning move count).
	void updateWeights();

};
