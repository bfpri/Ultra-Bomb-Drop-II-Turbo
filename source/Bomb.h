#ifndef BOMB_H
#define BOMB_H
#include "Foo.h"
class AIPlayer;
class Bomb
{
private:
	int offSet;
	int yoffset;
	int frame;
	int spacepressed;
	int counter;

public: string killer_name;
		void makebomb(AIPlayer* x);
		void makebomb(Foo foo);
		Bomb();
		void handle_events();
		void showbomb();
		int getoffset();
		int getyoffset();
		int getcounter();
		void explosion();
		void kill(string n, string n1);
		void updatescores(int i);

};
#endif