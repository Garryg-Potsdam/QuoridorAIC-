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


public:
	string placeWalls(int player,int row, int col, string direction);
	Pawn pOne, pTwo;
	Board();	
	string PrintBoard();
	string movePawn(int player, string move);	

private:
	void setPawns();
	string PawnMove(Pawn &player, Direction d);
	

};