#ifndef LEVEL_H
#define LEVEL_H

#include "LocalPlayer.h"

#include <vector>

using namespace std;

#define LEVEL_COL 22
#define LEVEL_ROW 22

#define DESTROY_BLOCKS 20

typedef enum {
    GROUND,
    SOLID,
    BREAK
} Tile;

class Level {
  
    Tile board_data[LEVEL_ROW][LEVEL_COL];
    
    
    LocalPlayer* local;
    vector<Player*> players;
    
public:
    Level(); //Constructor to generate a random level
    
    void add_player(Player* player);
    void set_local(LocalPlayer* player);
    
    void generate(); //Generates a random level
    
    Tile get_tile(int x, int y);
	void set_tile(int x, int y);
    
    void update();
};

#endif