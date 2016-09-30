#include <iostream>
#include <string>
#include <queue>
using namespace std;


class Board {	

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

struct Square {
	int row;
	int col;
	bool seen;
	bool up, down, left, right;
};

// The game board of squares
struct GameBoard {
	Square board[9][9];
};

struct Pawn {
	int wallsLeft = 10;
	int row;
	int col;
};

struct Wall {
	int row, col;
	string dir;
};

public:	
	Board();	
	string PrintBoard();
	bool movePawn(int player, string move);	
	bool placeWalls(int player, int row, int col, string direction);
	bool checkWinner();
	string getWinner();

private:
	GameBoard gb;	
	Pawn pOne, pTwo;
	int wallCounter = 0;
	Wall walls[20];
	void setPawns();
	bool PawnMove(Pawn &player, Direction d, int p);
	bool checkNotBlocked(int player);

};