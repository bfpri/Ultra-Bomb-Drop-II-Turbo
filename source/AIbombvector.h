#ifndef AIBOMBVECTOR_H
#define AIBOMBVECTOR_H
#include "bombvector.h"

using namespace std;

class AIbombvector
{
	
public:
	int counter;
	vector<Bomb> bombvect;
	void makebombs(AIPlayer foo);
	void showbombs();
	vector<Bomb> getbombvect();
	AIbombvector(){counter=0;}
};
#endif