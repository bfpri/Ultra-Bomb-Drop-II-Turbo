#ifndef BOMBVECTOR_H
#define BOMBVECTOR_H
#include "AIPlayer.h"

using namespace std;

class bombvector
{
	vector<Bomb> bombvect;
public:
	void handle_events(Foo foo);
	void makebombs(Foo foo);
	void showbombs();
	vector<Bomb> getbombvect();
};
#endif