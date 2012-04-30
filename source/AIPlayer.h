#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "Bomb.h"


class AIPlayer : public Foo {
public:
	int latestMove;	//value to determine proper graphic to use
				//1=up, 2=down, 3=right, 4=left

	 //Its rate of movement
    int velocity;
	int yvelocity;
	int offSet;
	int yoffset;
	AIPlayer();
	int isalive();
	void randStart(int size);
	int randMove();
	void update(int x);
	void resetTimer();
	bool checkmove(int i,bombvector b, AIbombvector b2);
	    //Its current frame
    int frame;
	int counter;
	int count;
    //Its animation status
    int status;
	void spawn();
	int move(bombvector b, AIbombvector b2);
	void show();
	int alive;
	void plantbomb(AIbombvector* b);
	int getoffset();
	int getyoffset();
	string name;
	int max_bombs;
	int checkforBombs(bombvector* b,AIbombvector*b2, int x, int y);

};
#endif