#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class Highscore {
	string scores[10];	

public: 

	Highscore();
	void readScores();

	void writeNewScore(int score);

	string getScoreString(int x);

	int getScore(int x);

	string* getScores();

	void overwriteScore(int place, int score);

	void resetScores();
};

#endif