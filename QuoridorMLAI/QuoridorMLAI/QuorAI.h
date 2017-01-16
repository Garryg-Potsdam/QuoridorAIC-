#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <string>
#include "DBConnection.h"


using namespace std;

class QuorAI {

    public:
        // CONSTRUCTOR
        QuorAI(int player);
	
        // Returns: Next move either a pawn move or a wall move
        string getRandomMove();
        
        // Returns: the next move the agent will make.
        string getNextMove();
	
        // Parameters: board - the most recent board configuration
        // Post-Condition: set the mostRecentBoard field
        void setMostRecentBoard(string board);
        
        // Notifies the database connector who won
        // Parameters: winner - the winner of the game.
        // Postcondition: ends the game.
        void giveWinner(int winner);

    private:
      bool firstTurn;
      int GameID;
      // The database connection
      DBConnection * dbc;
      // What player the ai is
      int player;
      // Postion into prevMoves array; How many bad moves we made.
      int countPrevMoves;
      // prev moves        
      string prevMoves[139];        
      // was the recent move valid
      bool wasValid;
      // The most recent board config
      string mostRecentBoard;
      // The last board config
      string prevBoard;

    	// Parameters: i - the int to convert to a string
    	// Post-Condition: turns an integer to a string
	    // Returns: the int as a string
      string intToString(int i);

      // Returns: a random move; either a pawn move or a wall placement.
      string makeRandomMove();

      // Returns: a random move to move a pawn.
      string makeRandomPawnMove();

      // Returns: a random wall to place.
      string makeRandomWall();
      
      // Remember the agent's previous state
      // Postconditions: requests the game state (board configuration) to be stored 
      //                 in the database
      void rememberPrevState();
      
      // Hashes the string of a given board configuration
      // Parameters: str - the board configuration needing to be hashed
      // Returns: the value after the hash
      unsigned int hashString(const std::string& str);
      
      // Determines a move intelligently by communicating to the database connector
      // Returns: the next move to make
      string makeIntelligentMove();

};
