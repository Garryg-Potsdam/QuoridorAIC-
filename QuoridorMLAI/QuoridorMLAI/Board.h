#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

// A board class for the game of Quoridor
class Board {	

// Directions that can be moved in the game
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UPLEFT,
	UPRIGHT,
	DOWNLEFT,
	DOWNRIGHT,
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN
};

// Squares are basically nodes that determine if the
// direction is desired is available
struct Square {
	int row;
	int col;
	bool up, down, left, right, seen;
};

// The game board of squares
struct GameBoard {
	Square * board[9][9];
};

// A  pawn is just a piece that gets moved around the board
// Pawns have a row and column and up to 10 walls per game
struct Pawn {
	int wallsLeft;
	int row;
	int col;
};

// A wall is a structure that blocks movement along a specific
// path
struct Wall {
	int row, col;
	string dir;
};

public:

	// Constructs the board
	Board();

	// Returns: the board as a string
	string toString();	

	// Returns: int for printing the winner
	int getWinner();
	
	// Parameters: player - the player whos pawn made a move
	//               move - the direction the player chose to move
	// Post-Condition: moves a pawn
	// Returns: true if successful false otherwise
	bool movePawn(int player, string move);

	// Parameters:    player - the player whos pawn made a move
	//                   row - the row the wall is attempted to be placed at
	//                   col - the column the wall is attempted to be placed at
	//             direction - the direction of the wall (horizontal, vertical)
	// Post-Condition: places a wall
	// Returns: true if successful false otherwise
	bool placeWalls(int player, int row, int col, string direction);

	// Returns: true if there is a winner false otherwise
	bool checkWinner();
	
	// Paramaters: i - int to turn to string
	// Returns: string of the passed in int
	string to_string(int i);
    
	// Paramaters: s - string to turn to int
	// Returns: int of the passed in string
	int stringToInt(string s);

private:	

	// The gameboard of squares
	GameBoard * gb;

	// The two pawns to be placed
	Pawn *pOne, *pTwo;

	// keeps track of our offset into the walls array
	int wallCounter;

	// All the walls that have been placed so far
	Wall walls[20];

	// Post-Condition: Sets the pawns at their starting locations
	void setPawns();

	// Parameters:        player - the pawn to be moved
	//                 direction - the direction the player wants to move
	//             currentPlayer - the current players number
	// Post-Condition: alters a pawns location
	// Returns: true if successful false otherwise
	bool PawnMove(Pawn &player, Direction d, int currentPlayer);

	// Post-Condition: checks if a player is blocked from goal or not
	// Returns: true if not blocked from goal false otherwise
	bool checkNotBlocked();
};
