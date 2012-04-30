#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>
//#include <curses.h>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "Score.h"
#include "Highscore.h"
#include "Level.h"
#include "AIPlayer.h"
#include "LocalPlayer.h"

using namespace std;

class Game{
	LocalPlayer p1, p2, p3, p4;
	AIPlayer c1, c2, c3, c4;
	int gameType;		// 0 = multiplayer; 1 = singleplayer

	struct Bomb {
	int radius;
	int timer;
	int loc_x;
	int loc_y;
	string killer_name;
	} ;
public:
	Level gameBoard;
	vector<Bomb> bombs;
	Game();
	void randAIStart(int n);
	void setLocalName(string s);
	void singlePlayer();
	void multiPlayer();
	void printBoard();
	int checkMove(AIPlayer c, int move);
	int checkMove(LocalPlayer c, int move);
	void setBomb(string n, int r, int x, int y);
	void bombDec();
	int checkforBombs(int x, int y);
	void blowUp(Bomb b);
	void setBombRadius(int x);
	void updateScores(int n);
	void winner(AIPlayer c);
	void saveScores();
	void kill(string n, string victim);
	void displayAI(AIPlayer ai);

};

#endif