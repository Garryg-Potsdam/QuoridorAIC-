#include <iostream>
#include <string>

using namespace std;

class Board {

public:
	Board();	
	string toString();
	void placePawn(int row, int col);
	void removePawn(int row, int col);
	void setPawns();

};