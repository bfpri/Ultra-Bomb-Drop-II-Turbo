#ifndef FOO_H
#define FOO_H

#include <string>

class bombvector;
class AIbombvector;
class Foo
{

protected:
    //The offset
    
    //Its rate of movement
   
    //Its current frame
    int frame;
	int count;
    //Its animation status
    int status;
	//string name;
    
    int score;
   // Score myScore;
    int bombTimer;
    int max_bombs;
    int blast_pow;

    public:
	
	Score myScore;
	string name;
	void randStart(int size);
	int offSet;
	int yoffset;
	int alive;
	int isalive();
	void spawn();
	int getstatus();
	int getoffset();
	int getyoffset();
	 int velocity;
	int yvelocity;
	void update(int x, int y);
    //Initializes the variables
    Foo();
	int checkmove(int i, bombvector b, AIbombvector b2);
	void makebomb();
    //Handles input
    void handle_events();
	int checkforBombs(bombvector* b, AIbombvector* b2, int x, int y);
	
	
    //Moves the stick figure
    int move(bombvector b, AIbombvector b2);

    //Shows the stick figure
    void show();
};
#endif