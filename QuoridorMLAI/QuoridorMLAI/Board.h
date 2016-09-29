#include <iostream>
#include <string>

using namespace std;


class Board {	

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
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
	int wallCounter = 0;
	Wall walls[20];
	Pawn pOne, pTwo;
	Board();	
	string PrintBoard();
	bool movePawn(int player, string move);	
	bool placeWalls(int player, int row, int col, string direction);

private:
	void setPawns();
	bool PawnMove(Pawn &player, Direction d);
	

};