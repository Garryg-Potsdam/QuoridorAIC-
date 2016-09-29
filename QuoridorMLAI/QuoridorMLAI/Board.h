#include <iostream>
#include <string>

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
	Pawn pOne, pTwo;
	int wallCounter = 0;
	Wall walls[20];
	void setPawns();
	bool PawnMove(Pawn &player, Direction d, int p);
	

};