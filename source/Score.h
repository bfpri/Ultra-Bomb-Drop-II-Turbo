#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>


using namespace std;
 
/* **** SCORING SYSTEM

	Last Player Standing =  50 pts
	Kill Opposing Player = 100 pts
	Player Last 3 Alive  =  20 pts
	Player Last 2 Alive  =  10 pts

******* */

class Score {

public:
	int myScore;

	Score();

	void score_lastAlive();
	void score_kill();
	void score_3Alive();
	void score_2Alive();
	void score_inc(int x);
	int getScore();

};

#endif