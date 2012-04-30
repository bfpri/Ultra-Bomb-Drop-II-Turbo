#include "SDL.h"
#include "SDL_image.h"

#include <stdio.h>
#include <string>
#include "Timer.h"
#include "Score.h"

#include "Level.h"
#include "AIbombvector.h"
using namespace std;
//The frames per second
const int FRAMES_PER_SECOND = 10;

//The direction status of the bomberman figure
const int FOO_RIGHT = 1;
const int FOO_LEFT = 2;
const int FOO_UP = 3;
const int FOO_DOWN =4;
   bool quit = false;
	 int animationRate = 12;
    int animationLength = 13;
    int startTime = SDL_GetTicks(); 
#define COLORKEY 255, 0, 255
AIPlayer c1, c2, c3, c4;
Foo p1;
class bombvector;
//The surfaces
SDL_Surface *bomb=NULL;
SDL_Surface *foo = NULL;
SDL_Surface *dots = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *AI=NULL;
int alpha = SDL_ALPHA_OPAQUE;
//The dimenstions of the bomberman figure
const int FOO_WIDTH = 32;
const int FOO_HEIGHT = 32;
int counting =0;
const int BOMB_WIDTH= 32;
const int BOMB_HEIGHT=32;
//The event structure
SDL_Event event;
int keypressed=0;
int keyup =1;
 Level* lvl = new Level();
//The portions of the sprite map to be blitted
SDL_Rect clip[ 4 ];
SDL_Rect bombclip[4];
//The areas of the sprite sheet
SDL_Rect clipsRight[ 9 ];
SDL_Rect clipsLeft[ 9 ];
SDL_Rect clipsUp [9];
SDL_Rect clipsDown [9];

SDL_Rect clipsRight2[ 9 ];
SDL_Rect clipsLeft2[ 9 ];
SDL_Rect clipsUp2 [9];
SDL_Rect clipsDown2 [9];

inline SDL_Surface *ImgLoader(char *file,bool bCKey, int r , int g , int b , int alpha)
{
    SDL_Surface *pic;
    pic = IMG_Load(file); // From SDL_image.h , load the image to pic
    // Log error message into stderr.txt if happened
    if(pic==NULL) fprintf(stderr,"Missing image %s : %s\n",file,IMG_GetError());
    if( bCKey ) {
        // Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.
       SDL_SetColorKey(pic,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic->format,r,g,b));
         }
    if(alpha) SDL_SetAlpha(pic, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha);
    // This function takes a surface and copies it to a new surface of the 
    // pixel format and colors of the video framebuffer, suitable for fast 
    // blitting onto the display surface.
    pic = SDL_DisplayFormat(pic);
    return (pic);
}

inline SDL_Surface *ImgLoader(char *file)       
                { return ImgLoader(file,1,0,0,0,0) ; }
inline SDL_Surface *ImgLoader(char *file,bool bCKey)
                { return ImgLoader(file,1,255,255,255,0) ; }




SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
	
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old surface
        SDL_FreeSurface( loadedImage );
        
        //If the surface was optimized
       // if( optimizedImage != NULL )
       // {
            //Color key surface
			 //Map the color key
         //   Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
          //  SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        
   		 //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            
		//}
	
	
	}
    
    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


//Screen attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

bool load_files()
{
    //Load the sprite map
    dots = IMG_Load( "tiles3.gif" );
	 
      
    //If there was an problem loading the sprite map
    if( dots == NULL )
    {
        return false;
    }
	//foo = ImgLoader( "costume2.gif" ,1,255,255,255,0);
	//foo = ImgLoader( "costume2.gif" ,1);
	foo=IMG_Load("costume6.gif");
	if( foo == NULL )
    {
        return false;
    }
    bomb=IMG_Load("bomb2.gif");
	if( bomb == NULL )
    {
        return false;
    }
	AI=IMG_Load("costume7.gif");
    //If eveything loaded fine
    return true;
}

//bool quit = false;
void set_clips()
{
    //Clip the sprites
    clipsRight[ 0 ].x = 0;
    clipsRight[ 0 ].y = 104;
    clipsRight[ 0 ].w = FOO_WIDTH-1;
    clipsRight[ 0 ].h = FOO_HEIGHT;

    clipsRight[ 1 ].x = FOO_WIDTH-6;
    clipsRight[ 1 ].y = 104;
    clipsRight[ 1 ].w = FOO_WIDTH-1;
    clipsRight[ 1 ].h = FOO_HEIGHT;

    clipsRight[ 2 ].x = FOO_WIDTH * 2-12;
    clipsRight[ 2 ].y = 104;
    clipsRight[ 2 ].w = FOO_WIDTH-1;
    clipsRight[ 2 ].h = FOO_HEIGHT;

    clipsRight[ 3 ].x = FOO_WIDTH * 3-18;
    clipsRight[ 3 ].y = 104;
    clipsRight[ 3 ].w = FOO_WIDTH-1;
    clipsRight[ 3 ].h = FOO_HEIGHT;
	
	clipsRight[ 4 ].x = FOO_WIDTH * 4-24;
    clipsRight[ 4 ].y = 104;
    clipsRight[ 4 ].w = FOO_WIDTH-1;
    clipsRight[ 4 ].h = FOO_HEIGHT;
	
	clipsRight[ 5 ].x = FOO_WIDTH * 5-30;
    clipsRight[ 5 ].y = 104;
    clipsRight[ 5 ].w = FOO_WIDTH-1;
    clipsRight[ 5 ].h = FOO_HEIGHT;
	
	clipsRight[ 6 ].x = FOO_WIDTH * 6-36;
    clipsRight[ 6 ].y = 104;
    clipsRight[ 6 ].w = FOO_WIDTH-6;
    clipsRight[ 6 ].h = FOO_HEIGHT;
	
	clipsRight[ 7 ].x = FOO_WIDTH * 7-42;
    clipsRight[ 7 ].y = 104;
    clipsRight[ 7 ].w = FOO_WIDTH-1;
    clipsRight[ 7 ].h = FOO_HEIGHT;

	clipsRight[ 8 ].x = FOO_WIDTH * 7-42;
    clipsRight[ 8 ].y = 104;
    clipsRight[ 8 ].w = FOO_WIDTH-1;
    clipsRight[ 8 ].h = FOO_HEIGHT;

    clipsLeft[ 0 ].x = 0;
    clipsLeft[ 0 ].y = 38;
    clipsLeft[ 0 ].w = FOO_WIDTH-1;
    clipsLeft[ 0 ].h = FOO_HEIGHT;

    clipsLeft[ 1 ].x = FOO_WIDTH-6;
    clipsLeft[ 1 ].y = 38;
    clipsLeft[ 1 ].w = FOO_WIDTH-1;
    clipsLeft[ 1 ].h = FOO_HEIGHT;

    clipsLeft[ 2 ].x = FOO_WIDTH * 2-12;
    clipsLeft[ 2 ].y = 38;
    clipsLeft[ 2 ].w = FOO_WIDTH-1;
    clipsLeft[ 2 ].h = FOO_HEIGHT;

    clipsLeft[ 3 ].x = FOO_WIDTH * 3-18;
    clipsLeft[ 3 ].y = 38;
    clipsLeft[ 3 ].w = FOO_WIDTH-1;
    clipsLeft[ 3 ].h = FOO_HEIGHT;

	clipsLeft[ 4 ].x = FOO_WIDTH*4-24;
    clipsLeft[ 4 ].y = 38;
    clipsLeft[ 4 ].w = FOO_WIDTH-1;
    clipsLeft[ 4 ].h = FOO_HEIGHT;

	clipsLeft[ 5 ].x = FOO_WIDTH*5-30;
    clipsLeft[ 5 ].y = 38;
    clipsLeft[ 5 ].w = FOO_WIDTH-1;
    clipsLeft[ 5 ].h = FOO_HEIGHT;

	clipsLeft[ 6 ].x = FOO_WIDTH*6-36;
    clipsLeft[ 6 ].y = 38;
    clipsLeft[ 6 ].w = FOO_WIDTH-6;
    clipsLeft[ 6 ].h = FOO_HEIGHT;

	clipsLeft[ 7 ].x = FOO_WIDTH*7-42;
    clipsLeft[ 7 ].y = 38;
    clipsLeft[ 7 ].w = FOO_WIDTH-1;
    clipsLeft[ 7 ].h = FOO_HEIGHT;

	clipsLeft[ 8 ].x = FOO_WIDTH*7-42;
    clipsLeft[ 8 ].y = 38;
    clipsLeft[ 8 ].w = FOO_WIDTH-1;
    clipsLeft[ 8 ].h = FOO_HEIGHT;

	clipsUp[0].x=0;
	clipsUp[0].y=71;
	clipsUp[ 0 ].w = FOO_WIDTH-3;
    clipsUp[ 0 ].h = FOO_HEIGHT;

	clipsUp[ 1 ].x = FOO_WIDTH-4;
    clipsUp[ 1 ].y = 71;
    clipsUp[ 1 ].w = FOO_WIDTH-3;
    clipsUp[ 1 ].h = FOO_HEIGHT;

    clipsUp[ 2 ].x = 52;
    clipsUp[ 2 ].y = 71;
    clipsUp[ 2 ].w = FOO_WIDTH-3;
    clipsUp[ 2 ].h = FOO_HEIGHT;

    clipsUp[ 3 ].x = 84;
    clipsUp[ 3 ].y = 69;
    clipsUp[ 3 ].w = FOO_WIDTH-3;
    clipsUp[ 3 ].h = FOO_HEIGHT;

	clipsUp[ 4 ].x = 108;
    clipsUp[ 4 ].y = 71;
    clipsUp[ 4 ].w = FOO_WIDTH-3;
    clipsUp[ 4 ].h = FOO_HEIGHT;

	clipsUp[ 5 ].x = 135;
    clipsUp[ 5 ].y = 71;
    clipsUp[ 5 ].w = FOO_WIDTH-3;
    clipsUp[ 5 ].h = FOO_HEIGHT;

	clipsUp[ 6 ].x = 161;
    clipsUp[ 6 ].y = 71;
    clipsUp[ 6].w = FOO_WIDTH-3;
    clipsUp[ 6 ].h = FOO_HEIGHT;

	clipsUp[ 7 ].x = 189;
    clipsUp[ 7 ].y = 71;
    clipsUp[ 7 ].w = FOO_WIDTH-6;
    clipsUp[ 7 ].h = FOO_HEIGHT;
	
	clipsUp[ 8 ].x = 189;
    clipsUp[ 8 ].y = 71;
    clipsUp[ 8 ].w = FOO_WIDTH-6;
    clipsUp[ 8 ].h = FOO_HEIGHT;
	
	
	clipsDown[0].x=0;
	clipsDown[0].y=0;
	clipsDown[ 0 ].w = FOO_WIDTH-3;
    clipsDown[ 0 ].h = FOO_HEIGHT;

	clipsDown[ 1 ].x = FOO_WIDTH-5;
    clipsDown[ 1 ].y = 0;
    clipsDown[ 1 ].w = FOO_WIDTH-3;
    clipsDown[ 1 ].h = FOO_HEIGHT;

    clipsDown[ 2 ].x = FOO_WIDTH * 2-10;
    clipsDown[ 2 ].y = 0;
    clipsDown[ 2 ].w = FOO_WIDTH-3;
    clipsDown[ 2 ].h = FOO_HEIGHT;

    clipsDown[ 3 ].x = FOO_WIDTH * 3-15;
    clipsDown[ 3 ].y = 0;
    clipsDown[ 3 ].w = FOO_WIDTH-3;
    clipsDown[ 3 ].h = FOO_HEIGHT;

	clipsDown[ 4 ].x = FOO_WIDTH * 4-20;
    clipsDown[ 4 ].y = 0;
    clipsDown[ 4 ].w = FOO_WIDTH-3;
    clipsDown[ 4 ].h = FOO_HEIGHT;

	clipsDown[ 5 ].x = FOO_WIDTH * 5-25;
    clipsDown[ 5 ].y = 0;
    clipsDown[ 5 ].w = FOO_WIDTH-3;
    clipsDown[ 5 ].h = FOO_HEIGHT;

	clipsDown[ 6 ].x = FOO_WIDTH * 6-30;
    clipsDown[ 6 ].y = 0;
    clipsDown[ 6 ].w = FOO_WIDTH-3;
    clipsDown[ 6 ].h = FOO_HEIGHT;

	clipsDown[ 7 ].x = FOO_WIDTH * 7-35;
    clipsDown[ 7 ].y = 0;
    clipsDown[ 7 ].w = FOO_WIDTH-6;
    clipsDown[ 7 ].h = FOO_HEIGHT;

	clipsDown[ 8 ].x = FOO_WIDTH * 7-35;
    clipsDown[ 8 ].y = 0;
    clipsDown[ 8 ].w = FOO_WIDTH-6;
    clipsDown[ 8 ].h = FOO_HEIGHT;

	clipsRight2[ 0 ].x = 0;
    clipsRight2[ 0 ].y = 104;
    clipsRight2[ 0 ].w = FOO_WIDTH-1;
    clipsRight2[ 0 ].h = FOO_HEIGHT;

    clipsRight2[ 1 ].x = FOO_WIDTH-6;
    clipsRight2[ 1 ].y = 104;
    clipsRight2[ 1 ].w = FOO_WIDTH-1;
    clipsRight2[ 1 ].h = FOO_HEIGHT;

    clipsRight2[ 2 ].x = FOO_WIDTH * 2-12;
    clipsRight2[ 2 ].y = 104;
    clipsRight2[ 2 ].w = FOO_WIDTH-1;
    clipsRight2[ 2 ].h = FOO_HEIGHT;

    clipsRight2[ 3 ].x = FOO_WIDTH * 3-18;
    clipsRight2[ 3 ].y = 104;
    clipsRight2[ 3 ].w = FOO_WIDTH-1;
    clipsRight2[ 3 ].h = FOO_HEIGHT;
	
	clipsRight2[ 4 ].x = FOO_WIDTH * 4-24;
    clipsRight2[ 4 ].y = 104;
    clipsRight2[ 4 ].w = FOO_WIDTH-1;
    clipsRight2[ 4 ].h = FOO_HEIGHT;
	
	clipsRight2[ 5 ].x = FOO_WIDTH * 5-30;
    clipsRight2[ 5 ].y = 104;
    clipsRight2[ 5 ].w = FOO_WIDTH-1;
    clipsRight2[ 5 ].h = FOO_HEIGHT;
	
	clipsRight2[ 6 ].x = FOO_WIDTH * 6-36;
    clipsRight2[ 6 ].y = 104;
    clipsRight2[ 6 ].w = FOO_WIDTH-6;
    clipsRight2[ 6 ].h = FOO_HEIGHT;
	
	clipsRight2[ 7 ].x = FOO_WIDTH * 7-42;
    clipsRight2[ 7 ].y = 104;
    clipsRight2[ 7 ].w = FOO_WIDTH-1;
    clipsRight2[ 7 ].h = FOO_HEIGHT;

	clipsRight2[ 8 ].x = FOO_WIDTH * 7-42;
    clipsRight2[ 8 ].y = 104;
    clipsRight2[ 8 ].w = FOO_WIDTH-1;
    clipsRight2[ 8 ].h = FOO_HEIGHT;

    clipsLeft2[ 0 ].x = 0;
    clipsLeft2[ 0 ].y = 38;
    clipsLeft2[ 0 ].w = FOO_WIDTH-1;
    clipsLeft2[ 0 ].h = FOO_HEIGHT;

    clipsLeft2[ 1 ].x = FOO_WIDTH-6;
    clipsLeft2[ 1 ].y = 38;
    clipsLeft2[ 1 ].w = FOO_WIDTH-1;
    clipsLeft2[ 1 ].h = FOO_HEIGHT;

    clipsLeft2[ 2 ].x = FOO_WIDTH * 2-12;
    clipsLeft2[ 2 ].y = 38;
    clipsLeft2[ 2 ].w = FOO_WIDTH-1;
    clipsLeft2[ 2 ].h = FOO_HEIGHT;

    clipsLeft2[ 3 ].x = FOO_WIDTH * 3-18;
    clipsLeft2[ 3 ].y = 38;
    clipsLeft2[ 3 ].w = FOO_WIDTH-1;
    clipsLeft2[ 3 ].h = FOO_HEIGHT;

	clipsLeft2[ 4 ].x = FOO_WIDTH*4-24;
    clipsLeft2[ 4 ].y = 38;
    clipsLeft2[ 4 ].w = FOO_WIDTH-1;
    clipsLeft2[ 4 ].h = FOO_HEIGHT;

	clipsLeft2[ 5 ].x = FOO_WIDTH*5-30;
    clipsLeft2[ 5 ].y = 38;
    clipsLeft2[ 5 ].w = FOO_WIDTH-1;
    clipsLeft2[ 5 ].h = FOO_HEIGHT;

	clipsLeft2[ 6 ].x = FOO_WIDTH*6-36;
    clipsLeft2[ 6 ].y = 38;
    clipsLeft2[ 6 ].w = FOO_WIDTH-6;
    clipsLeft2[ 6 ].h = FOO_HEIGHT;

	clipsLeft2[ 7 ].x = FOO_WIDTH*7-42;
    clipsLeft2[ 7 ].y = 38;
    clipsLeft2[ 7 ].w = FOO_WIDTH-1;
    clipsLeft2[ 7 ].h = FOO_HEIGHT;

	clipsLeft2[ 8 ].x = FOO_WIDTH*7-42;
    clipsLeft2[ 8 ].y = 38;
    clipsLeft2[ 8 ].w = FOO_WIDTH-1;
    clipsLeft2[ 8 ].h = FOO_HEIGHT;

	clipsUp2[0].x=0;
	clipsUp2[0].y=71;
	clipsUp2[ 0 ].w = FOO_WIDTH-3;
    clipsUp2[ 0 ].h = FOO_HEIGHT;

	clipsUp2[ 1 ].x = FOO_WIDTH-4;
    clipsUp2[ 1 ].y = 71;
    clipsUp2[ 1 ].w = FOO_WIDTH-3;
    clipsUp2[ 1 ].h = FOO_HEIGHT;

    clipsUp2[ 2 ].x = 52;
    clipsUp2[ 2 ].y = 71;
    clipsUp2[ 2 ].w = FOO_WIDTH-3;
    clipsUp2[ 2 ].h = FOO_HEIGHT;

    clipsUp2[ 3 ].x = 84;
    clipsUp2[ 3 ].y = 69;
    clipsUp2[ 3 ].w = FOO_WIDTH-3;
    clipsUp2[ 3 ].h = FOO_HEIGHT;

	clipsUp2[ 4 ].x = 108;
    clipsUp2[ 4 ].y = 71;
    clipsUp2[ 4 ].w = FOO_WIDTH-3;
    clipsUp2[ 4 ].h = FOO_HEIGHT;

	clipsUp2[ 5 ].x = 135;
    clipsUp2[ 5 ].y = 71;
    clipsUp2[ 5 ].w = FOO_WIDTH-3;
    clipsUp2[ 5 ].h = FOO_HEIGHT;

	clipsUp2[ 6 ].x = 161;
    clipsUp2[ 6 ].y = 71;
    clipsUp2[ 6].w = FOO_WIDTH-3;
    clipsUp2[ 6 ].h = FOO_HEIGHT;

	clipsUp2[ 7 ].x = 189;
    clipsUp2[ 7 ].y = 71;
    clipsUp2[ 7 ].w = FOO_WIDTH-6;
    clipsUp2[ 7 ].h = FOO_HEIGHT;
	
	clipsUp2[ 8 ].x = 189;
    clipsUp2[ 8 ].y = 71;
    clipsUp2[ 8 ].w = FOO_WIDTH-6;
    clipsUp2[ 8 ].h = FOO_HEIGHT;
	
	
	clipsDown2[0].x=0;
	clipsDown2[0].y=0;
	clipsDown2[ 0 ].w = FOO_WIDTH-3;
    clipsDown2[ 0 ].h = FOO_HEIGHT;

	clipsDown2[ 1 ].x = FOO_WIDTH-5;
    clipsDown2[ 1 ].y = 0;
    clipsDown2[ 1 ].w = FOO_WIDTH-3;
    clipsDown2[ 1 ].h = FOO_HEIGHT;

    clipsDown2[ 2 ].x = FOO_WIDTH * 2-10;
    clipsDown2[ 2 ].y = 0;
    clipsDown2[ 2 ].w = FOO_WIDTH-3;
    clipsDown2[ 2 ].h = FOO_HEIGHT;

    clipsDown2[ 3 ].x = FOO_WIDTH * 3-15;
    clipsDown2[ 3 ].y = 0;
    clipsDown2[ 3 ].w = FOO_WIDTH-3;
    clipsDown2[ 3 ].h = FOO_HEIGHT;

	clipsDown2[ 4 ].x = FOO_WIDTH * 4-20;
    clipsDown2[ 4 ].y = 0;
    clipsDown2[ 4 ].w = FOO_WIDTH-3;
    clipsDown2[ 4 ].h = FOO_HEIGHT;

	clipsDown2[ 5 ].x = FOO_WIDTH * 5-25;
    clipsDown2[ 5 ].y = 0;
    clipsDown2[ 5 ].w = FOO_WIDTH-3;
    clipsDown2[ 5 ].h = FOO_HEIGHT;

	clipsDown2[ 6 ].x = FOO_WIDTH * 6-30;
    clipsDown2[ 6 ].y = 0;
    clipsDown2[ 6 ].w = FOO_WIDTH-3;
    clipsDown2[ 6 ].h = FOO_HEIGHT;

	clipsDown2[ 7 ].x = FOO_WIDTH * 7-35;
    clipsDown2[ 7 ].y = 0;
    clipsDown2[ 7 ].w = FOO_WIDTH-6;
    clipsDown2[ 7 ].h = FOO_HEIGHT;

	clipsDown2[ 8 ].x = FOO_WIDTH * 7-35;
    clipsDown2[ 8 ].y = 0;
    clipsDown2[ 8 ].w = FOO_WIDTH-6;
    clipsDown2[ 8 ].h = FOO_HEIGHT;

	bombclip[0].x=19;
	bombclip[0].y=71;
	bombclip[ 0 ].w = BOMB_WIDTH;
    bombclip[ 0 ].h = BOMB_HEIGHT;

	bombclip[ 1 ].x = 92;
    bombclip[ 1 ].y = 73;
    bombclip[ 1 ].w = BOMB_WIDTH;
    bombclip[ 1 ].h = BOMB_HEIGHT;

    bombclip[ 2 ].x = 174;
    bombclip[ 2 ].y = 73;
    bombclip[ 2 ].w = BOMB_WIDTH;
    bombclip[ 2 ].h = BOMB_HEIGHT;
	
	bombclip[ 3 ].x = 169;
    bombclip[ 3 ].y = 17;
    bombclip[ 3 ].w = BOMB_WIDTH;
    bombclip[ 3 ].h = BOMB_HEIGHT;

		

}
void clean_up()
{
    //Free the sprite map
    SDL_FreeSurface( dots );
    SDL_FreeSurface( foo );

    //Quit SDL
    SDL_Quit();
}
void AIbombvector::makebombs(AIPlayer foo){
	for(int i=0;i<bombvect.size();i++)
	bombvect[i].makebomb(&foo);
}
	void AIbombvector::showbombs(){
		counter++;
		if(counter%2000==0){
			c1.max_bombs=0;
			c2.max_bombs=0;
		}
		for(int i=0;i<bombvect.size();i++){
	bombvect[i].showbomb();
	if(bombvect[i].getcounter()>=32){
		bombvect[i].explosion();
		bombvect.erase(bombvect.begin()+i);
	}
	}
	}
	vector<Bomb> AIbombvector:: getbombvect(){
	return bombvect;
	
	}
void Foo::update(int x, int y){
	offSet=x;
	yoffset=y;

}
int Foo::getstatus(){
return status ;
}
int Foo::getoffset(){
return offSet;
}
int Foo::getyoffset(){
return yoffset;
}

Foo::Foo()
{
	count=0;
    //Initialize movement variables
    offSet = 0;
    velocity = 0;
	alive=1;
	

	//yoffset=SCREEN_HEIGHT-FOO_HEIGHT;
	yvelocity=0;
    //Initialize animation variables
    frame = 0;
    status = FOO_RIGHT;
}

void Foo::spawn(){
	bool flag=false;
for(int i = 1; i < LEVEL_ROW-1; ++i) {
        for(int j = 1; j < LEVEL_COL-1; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND&&(lvl->get_tile(j+1,i)==GROUND||lvl->get_tile(j-1,i)==GROUND||lvl->get_tile(j,i+1)==GROUND||lvl->get_tile(j,i-1)==GROUND)) {
                
				offSet=i*32;
				yoffset=j*32;
              flag=true;
				break;
            } 
        }
        if(flag)
			break;
		printf("\n");
    }
}
int AIPlayer::checkforBombs(bombvector* b, AIbombvector* b2, int x, int y){
	for(int z=0;z<b2->getbombvect().size();z++)
		if(((b2->getbombvect()[z].getoffset()/32) == (x/32)) && ((b2->getbombvect()[z].getyoffset()-10)/32) == (y/32))
			return 1;
	for(int z=0; z<b->getbombvect().size(); z++)
		if(((b->getbombvect()[z].getoffset()/32) == (x/32)) && ((b->getbombvect()[z].getyoffset()-10)/32) == (y/32))
			return 1;
	return 0;

}
int Foo::checkforBombs(bombvector* b, AIbombvector* b2, int x, int y){
	for(int z=0; z<b2->getbombvect().size(); z++)
		if(((b2->getbombvect()[z].getoffset()/32) == (x/32)) && ((b2->getbombvect()[z].getyoffset()-10)/32) == (y/32))
			return 1;
	
	for(int z=0; z<b->getbombvect().size(); z++)
		if(((b->getbombvect()[z].getoffset()/32) == (x/32)) && ((b->getbombvect()[z].getyoffset()-10)/32) == (y/32))
			return 1;
	return 0;

}

 Bomb::Bomb(){
offSet=0;
yoffset=0;
frame=0;
spacepressed=0;
counter=0;
}
int Bomb::getcounter(){
return counter;
}
int Bomb::getoffset(){
return offSet;
}
int Bomb::getyoffset(){
return yoffset;
}
void Bomb::makebomb(AIPlayer* foo){

	
	if(killer_name==foo->name){
		counter++;
		if(counter==1){
		if(foo->getoffset()%32==0)
        offSet=foo->getoffset();
		else
			if((foo->getoffset()+4)%32==0)
				offSet=foo->getoffset()+4;
			else
				if((foo->getoffset()-4)%32==0)
					offSet=foo->getoffset()-4;
		
	
		if(foo->getyoffset()%32==0)
        yoffset=foo->getyoffset()+10;
		else
			if((foo->getyoffset()+4)%32==0)
				yoffset=foo->getyoffset()+4+10;
			else
				if((foo->getyoffset()-4)%32==0)
					yoffset=foo->getyoffset()-4+10;
		
		}
    
    
     
    
	
	}


}
void Bomb::makebomb( Foo foo){
	counter++;
	if(counter==1){
		if(foo.getoffset()%32==0)
        offSet=foo.getoffset();
		else
			if((foo.getoffset()+4)%32==0)
				offSet=foo.getoffset()+4;
			else
				if((foo.getoffset()-4)%32==0)
					offSet=foo.getoffset()-4;
		
	
		if(foo.getyoffset()%32==0)
        yoffset=foo.getyoffset()+10;
		else
			if((foo.getyoffset()+4)%32==0)
				yoffset=foo.getyoffset()+4+10;
			else
				if((foo.getyoffset()-4)%32==0)
					yoffset=foo.getyoffset()-4+10;
		
	
    
    
     
    
	
	}
	


}
Score::Score(){
	myScore = 0;
}

void Score::score_lastAlive(){
	myScore += 50;
}

void Score::score_kill(){
	myScore += 100;
}

void Score::score_3Alive(){
	myScore += 20;
}
void Score::score_2Alive(){
	myScore += 10;
}

void Score::score_inc(int x){
	myScore += x;
}

int Score::getScore(){
	return myScore;
}
void Bomb::showbomb(){
	//if(spacepressed)
	if(counter<10)
	apply_surface( offSet, yoffset, bomb, screen, &bombclip[ 0 ] );
	if(counter>=10&&counter<20)
	apply_surface( offSet, yoffset, bomb, screen, &bombclip[ 1 ] );
	if(counter>=20&&counter<30)
	apply_surface( offSet, yoffset, bomb, screen, &bombclip[ 2 ] );
	if(counter>=30&&counter<32)
		apply_surface( offSet, yoffset, bomb, screen, &bombclip[ 3 ] );
		
	
}
void Bomb::kill(string n, string victim){
	if(victim != n){
	if(n == p1.name){
		p1.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else if(n == c1.name){
		c1.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else if(n == c2.name) {
		c2.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else {
		c3.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	}
	else
		cout << "Dumbass " << victim << " killed himself" << endl;
}
void Bomb::handle_events(){
if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_SPACE:spacepressed=1;
		}
    }
}
int AIPlayer::getoffset(){
return offSet;
}
int AIPlayer::getyoffset(){
return yoffset;
}
void AIPlayer::plantbomb(AIbombvector* b){
	if(count%10==0){

	
	Bomb x;
	if(max_bombs<3){
	x.killer_name=this->name;
	b->bombvect.push_back(x);
	max_bombs++;
	}
	}
	count++;
}
/*
void Bomb::updatescores(int n){
	if(n == 1) {
		if(c1.alive == 1)
			c1.myScore.score_inc(1);
		if(c2.alive == 1)
			c2.myScore.score_inc(1);
		if(c3.alive == 1)
			c3.myScore.score_inc(1);
		if(p1.alive == 1)
			p1.myScore.score_inc(1);
	}
	else{
	int total = c1.alive + c2.alive + c3.alive + p1.alive;	//determine how many are alive
	if(total == 1){		//determine which player was the last one alive
		if(c1.alive == 1){
			c1.myScore.score_lastAlive();
			//printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c1 has won the match with score: " << c1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c2.alive == 1){
			c2.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c2 has won the match with score: " << c2.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c3.alive == 1){
			c3.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c3 has won the match with score: " << c3.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else{
			p1.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << p1.name << " has won the match with score: " << p1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
	}
	if(total == 2){		//2 players are left alive
		if(c1.alive == 1 && c2.alive == 1){
			c1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(c1.alive == 1 && c3.alive == 1){
			c1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(c2.alive == 1 && c3.alive == 1){
			c2.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c1.alive == 1){
			p1.myScore.score_2Alive();
			c1.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c2.alive == 1){
			p1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c3.alive == 1){
			p1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
	}
	if(total == 3){		//3 players are left alive
		if(p1.alive == 0){
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();}
		else if(c1.alive == 0){
			p1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else if(c2.alive == 0){
			c1.myScore.score_3Alive();
			p1.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else{
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			p1.myScore.score_3Alive();
		}
	} }
}



//needs to be filled out to display proper AI animation
void Game::displayAI(AIPlayer ai){
	if(ai.latestMove == 1){
		//DISPLAY AI PLAYER MOVING UP
	}
	else if(ai.latestMove == 2){
		//DISPLAY AI PLAYER MOVING DOWN
	}
	else if(ai.latestMove == 3){
		//DISPLAY AI PLAYER MOVING RIGHT
	}
	else {
		//DISPLAY AI PLAYER MOVING LEFT
	}


}
*/
void Bomb::explosion(){
	int x = (this->offSet/32);
	int y = (this->yoffset/32);
	int count = 3;
	Tile t = lvl->get_tile(y,x);
	//up
	while(t != SOLID && x > 0 && count > 0){
		t = lvl->get_tile(y,x);
		if(t == BREAK)
			lvl->set_tile(y,x);
		if(((c1.getoffset()/32) == x) && ((c1.getyoffset()/32) == y) && c1.alive == 1){
			c1.alive = 0;
			////updatescores(0);
			
			kill(killer_name, c1.name);
		}
		if(c2.getoffset()/32 == x && c2.getyoffset()/32 == y && c2.alive == 1){
			c2.alive = 0;
			////updatescores(0);
			kill(killer_name, c2.name);
		}
		if(c3.getoffset()/32 == x && c3.getyoffset()/32 == y && c3.alive == 1){
			c3.alive = 0;
			//updatescores(0);
			kill(killer_name, c3.name);
		}
		if(p1.getoffset()/32 == x && p1.getyoffset()/32 == y && p1.isalive() == 1){
			p1.alive = 0;
			//updatescores(0);
			kill(killer_name, p1.name);
		}
		x--;
		count--;
	}
	count = 3;
	x =this->getoffset()/32;
	t = lvl->get_tile(y,x);
	while(t != SOLID && x < 22 && count > 0){
		t = lvl->get_tile(y,x);
		if(t == BREAK)
			lvl->set_tile(y,x);
		if(((c1.getoffset()/32) == x) && ((c1.getyoffset()/32) == y) && c1.alive == 1){
			c1.alive = 0;
			//updatescores(0);
			kill(killer_name, c1.name);
		}
		if(c2.getoffset()/32 == x && c2.getyoffset()/32 == y && c2.alive == 1){
			c2.alive = 0;
			//updatescores(0);
			kill(killer_name, c2.name);
		}
		if(c3.getoffset()/32 == x && c3.getyoffset()/32 == y && c3.alive == 1){
			c3.alive = 0;
			//updatescores(0);
			kill(killer_name, c3.name);
		}
		if(((p1.getoffset()/32) == x) && ((p1.getyoffset()/32) == y) && p1.alive == 1){
			p1.alive = 0;
			//updatescores(0);
			kill(killer_name, p1.name);
		}
		x++;
		count--;
	}
	count = 3;
	x = (this->getoffset()/32);
	t = lvl->get_tile(y,x);
	while(t != SOLID && y < 22 && count >0){
		t = lvl->get_tile(y,x);
		if(t == BREAK)
			lvl->set_tile(y,x);
		if(((c1.getoffset()/32) == x) && ((c1.getyoffset()/32) == y) && c1.alive == 1){
			c1.alive = 0;
			//updatescores(0);
			kill(killer_name, c1.name);
		}
		if(c2.getoffset()/32 == x && c2.getyoffset()/32 == y && c2.alive == 1){
			c2.alive = 0;
			//updatescores(0);
			kill(killer_name, c2.name);
		}
		if(c3.getoffset()/32 == x && c3.getyoffset()/32 == y && c3.alive == 1){
			c3.alive = 0;
			//updatescores(0);
			kill(killer_name, c3.name);
		}
		if(((p1.getoffset()/32) == x) && ((p1.getyoffset()/32) == y) && (p1.alive == 1)){
			p1.alive = 0;
			//updatescores(0);
			kill(killer_name, p1.name);
		}
		y++;
		count--;
	}
	count = 3;
	y = (this->getyoffset()/32);
	t = lvl->get_tile(y,x);
	while(t != SOLID && y > 0 && count >0){
		t = lvl->get_tile(y,x);
		if(((c1.getoffset()/32) == x) && ((c1.getyoffset()/32) == y) && c1.alive == 1){
			c1.alive = 0;
			//updatescores(0);
			kill(killer_name, c1.name);
		}
		if(c2.getoffset()/32 == x && c2.getyoffset()/32 == y && c2.alive == 1){
			c2.alive = 0;
			//updatescores(0);
			kill(killer_name, c2.name);
		}
		if(c3.getoffset()/32 == x && c3.getyoffset()/32 == y && c3.alive == 1){
			c3.alive = 0;
			//updatescores(0);
			kill(killer_name, c3.name);
		}
		if(p1.getoffset()/32 == x && p1.getyoffset()/32 == y && p1.alive == 1){
			p1.alive = 0;
			//updatescores(0);
			kill(killer_name, p1.name);
		}
		if(t == BREAK)
			lvl->set_tile(y,x);
		y--;
		count--;
	}
	count = 3;
	y = this->getyoffset()/32;
	t = lvl->get_tile(y,x);
}

//used to update the scores of all players based
//on who's alive and the time
//
//if n == 1, all players alive receive score += 1
//else, updateScores awards points to players for being the last, last 2, or last 3
//players left alive in the game
		/*
void Game::updateScores(int n){
	if(n == 1) {
		if(c1.alive == 1)
			c1.myScore.score_inc(1);
		if(c2.alive == 1)
			c2.myScore.score_inc(1);
		if(c3.alive == 1)
			c3.myScore.score_inc(1);
		if(p1.alive == 1)
			p1.myScore.score_inc(1);
	}
	else{
	int total = c1.alive + c2.alive + c3.alive + p1.alive;	//determine how many are alive
	if(total == 1){		//determine which player was the last one alive
		if(c1.alive == 1){
			c1.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c1 has won the match with score: " << c1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c2.alive == 1){
			c2.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c2 has won the match with score: " << c2.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c3.alive == 1){
			c3.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c3 has won the match with score: " << c3.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else{
			p1.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << p1.name << " has won the match with score: " << p1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
	}
	if(total == 2){		//2 players are left alive
		if(c1.alive == 1 && c2.alive == 1){
			c1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(c1.alive == 1 && c3.alive == 1){
			c1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(c2.alive == 1 && c3.alive == 1){
			c2.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c1.alive == 1){
			p1.myScore.score_2Alive();
			c1.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c2.alive == 1){
			p1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c3.alive == 1){
			p1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
	}
	if(total == 3){		//3 players are left alive
		if(p1.alive == 0){
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();}
		else if(c1.alive == 0){
			p1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else if(c2.alive == 0){
			c1.myScore.score_3Alive();
			p1.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else{
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			p1.myScore.score_3Alive();
		}
	} }


}
*/
vector<Bomb> bombvector::getbombvect(){
	return bombvect;
}
void bombvector::makebombs(Foo foo){
	if(bombvect.size()==0)
		printf("dog");
	for(int i=0;i<bombvect.size();i++)
	bombvect[i].makebomb(foo);
}
void bombvector::showbombs(){
	for(int i=0;i<bombvect.size();i++){
	bombvect[i].showbomb();
	if(bombvect[i].getcounter()>=32){
		bombvect[i].explosion();
		bombvect.erase(bombvect.begin()+i);
	}
	}
}
void bombvector::handle_events(Foo foo){
	if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        if( event.key.keysym.sym==SDLK_SPACE ){
        
            Bomb bomb;
			//if(foo.getstatus()==FOO_RIGHT&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2)/64,(foo.getoffset()+FOO_WIDTH+BOMB_WIDTH)/64)==GROUND&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-5)/64,(foo.getoffset()+FOO_WIDTH+BOMB_WIDTH)/64)==GROUND)
			bombvect.push_back(bomb); 
			//if(foo.getstatus()==FOO_LEFT&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2)/64,(foo.getoffset()-(BOMB_WIDTH-10))/64)==GROUND&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT)/64,(foo.getoffset()-(BOMB_WIDTH-10))/64)==GROUND)
			

		}
		
    }
}






AIPlayer::AIPlayer(){
	
	alive = 1;
	offSet =0;
	counter=0;
	count=0;
	yoffset =0;
	max_bombs =0;
	score=0;
	blast_pow=1;
	bombTimer = 3;
	status=FOO_RIGHT;
}

int AIPlayer::isalive(){
return alive;
}
void AIPlayer::resetTimer(){
	bombTimer = 3;
}

int AIPlayer::move(bombvector b, AIbombvector b2){
	
	//velocity=4;
		
	
	
	//offSet+=velocity;
		

	//Move
	
	if(alive){
	counter++;
	int i=0;
	if(counter==9)
		counter=1;
	if(counter==1){
		
		velocity=0;
		yvelocity=0;
	i=c1.randMove();
    while(checkmove(i,b,b2) == 0){
			i = c1.randMove();
		}
	
	  switch(i)
        {
			
	  case 1:velocity=FOO_WIDTH/8; status=FOO_RIGHT; break;
	  case 2: velocity =-( FOO_WIDTH/8) ;status=FOO_LEFT;break;
	  case 3: yvelocity=-(FOO_HEIGHT/8); status=FOO_UP;break;
	  case 4: yvelocity =(FOO_HEIGHT/8);status=FOO_DOWN; break;
			
		}
	}
	
	offSet += velocity;
	yoffset += yvelocity;
	
	}
	else
		if(!alive){
			offSet=-10;
			yoffset=-10;
		}
	
	/*
    //Keep the stick figure in bounds
    if( ( offSet< 32 ) || ( offSet + FOO_WIDTH>(21*32)))
    {
       
		offSet -= velocity;
		return 1;
	  }
//	else
	 if((yoffset<32)||(yoffset+ FOO_HEIGHT>21*32))
	 {
		 
		 yoffset -= yvelocity;
		return 1;
	 }
	 
	 if(status == FOO_UP&&yvelocity<0){		//CHECK MOVE UP
	//can't move through other players
		
		if((c2.offSet == this->offSet && c2.yoffset == this->yoffset && c2.alive == 1) || (c1.offSet == this->offSet && c1.yoffset ==this->yoffset && c1.alive == 1) || (c3.offSet== this->offSet && c3.yoffset == this->yoffset && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		 if((lvl->get_tile(((yoffset+1)/32),((offSet)/32))!=GROUND))
		 {
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		 if(checkforBombs(&b,this->offSet, this->yoffset+1) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
	
	}
	if(status == FOO_DOWN&&yvelocity>0){		//CHECK MOVE DOWN
	//can't move through other players
			if((c2.offSet == this->offSet && c2.yoffset == this->yoffset && c2.alive == 1) || (c1.offSet == this->offSet && c1.yoffset ==this->yoffset && c1.alive == 1) || (c3.offSet== this->offSet && c3.yoffset == this->yoffset && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		if((lvl->get_tile(((yoffset+FOO_HEIGHT-1)/32),((offSet)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,this->offSet, this->yoffset+FOO_HEIGHT-1) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
	}
	if(status == FOO_RIGHT&&velocity>0){		//CHECK MOVE RIGHT
	//can't move through other players
			if((c2.offSet == this->offSet && c2.yoffset == this->yoffset && c2.alive == 1) || (c1.offSet == this->offSet && c1.yoffset ==this->yoffset && c1.alive == 1) || (c3.offSet== this->offSet && c3.yoffset == this->yoffset && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		if((lvl->get_tile(((yoffset)/32),((offSet+FOO_WIDTH-1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,this->offSet+FOO_WIDTH-1, this->yoffset) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
	}
	if(status == FOO_LEFT&&velocity<0){		//CHECK MOVE LEFT
	//can't move through other players
		if((c2.offSet == this->offSet && c2.yoffset == this->yoffset && c2.alive == 1) || (c1.offSet == this->offSet && c1.yoffset ==this->yoffset && c1.alive == 1) || (c3.offSet== this->offSet && c3.yoffset == this->yoffset && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		 if((lvl->get_tile(((yoffset)/32),((offSet+1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,this->offSet+1, this->yoffset) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
		
	}
	*/

return 0;
}
void AIPlayer::show(){
	if(alive){
	if( velocity < 0 )
    {
        //Set the animation to left
        status = FOO_LEFT;

        //Move to the next frame in the animation
        frame++;
    }
    //If Foo is moving right
    else if( velocity > 0 )
    {
        //Set the animation to right
        status = FOO_RIGHT;
		//isstill=false;
		//for( int i=0;i<4;i++) {
		//apply_surface( offSet+=16, yoffset, foo, screen, &clipsRight[ frame ] );
        //Move to the next frame in the animation
        //if(count%2==1)
		//SDL_Delay(200);
		//count++;
		//if(count==5){
		frame++;
		//count=0;
		//}
		//frameToDraw = ((SDL_GetTicks() - startTime) * animationRate / 1000) % animationLength;
		
		//counting++;
		//if(keypressed==true&&counting==40){
			//velocity-=(FOO_WIDTH/8);
			counting=0;
			//keypressed=false;
		//}
		
		//}
    }
	//If Foo is moving up
	else if(yvelocity<0)
	{
		 //Set the animation to up
		status = FOO_UP;
		//Move to the next frame in the animation
		frame++;
	}
	//If Foo is moving down
	else if (yvelocity>0)
	{
		//Set the animation to down
		status=FOO_DOWN;
		//Move to the next frame in the animation
		frame++;
		//frame = (SDL_GetTicks() / 500) % 4; 
//		frameToDraw = ((SDL_GetTicks() - startTime) * animationRate / 1000) % animationLength;
		
	
	}
    //If Foo standing
    else
    {
        //Restart the animation
       
		frame = 0;
    }

    //Loop the animation
    if( frame >= 8 )
    {
       
		frame = 0;
    }

    //Show the stick figure
    if( status == FOO_RIGHT )
    {
	
		
		//frameToDraw = ((SDL_GetTicks() - startTime) * animationRate / 1000) % animationLength;
       
		apply_surface( offSet, yoffset, AI, screen, &clipsRight[ frame] );
		
	}
    else if( status == FOO_LEFT )
    {
        apply_surface( offSet, yoffset, AI, screen, &clipsLeft[ frame ] );
    }
	else if(status== FOO_UP)
	{
		 apply_surface( offSet, yoffset, AI, screen, &clipsUp[ frame ] );
	}
	else if (status == FOO_DOWN)
	{
		apply_surface( offSet, yoffset, AI, screen, &clipsDown[ frame ] );
	}
	}
	//else
		//apply_surface(-5,-5, foo, screen, &clipsDown[ frame ] );

}
void AIPlayer::spawn(){

	bool flag=false;
for(int i = 1; i < LEVEL_ROW-1; ++i) {
        for(int j = LEVEL_COL-1; j >0; --j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND&&(lvl->get_tile(j+1,i)==GROUND||lvl->get_tile(j-1,i)==GROUND||lvl->get_tile(j,i+1)==GROUND||lvl->get_tile(j,i-1)==GROUND)) {
                
				Foo::offSet=i*32;
				offSet=i*32;
				Foo::yoffset=j*32;
				yoffset=j*32;
				flag=true;
				break;
            } 
        }
        if(flag)
			break;
		printf("\n");
    }

}
int AIPlayer::randMove(){
	int rm;	//1 = UP; 2 = DOWN; 3 = RIGHT; 4 = LEFT
	rm = rand() % 4 + 1;
	return rm;
}

void AIPlayer::randStart(int size){
	int rm;
	rm = rand() % size;
	offSet = rm*32;
	rm = rand() % size;
	yoffset= rm*32;
}
void Foo::randStart(int size){
	int rm;
	rm = rand() % size;
	offSet = rm*32;
	rm = rand() % size;
	yoffset= rm*32;
}

void AIPlayer::update(int x){
	
}
bool AIPlayer::checkmove(int i, bombvector b, AIbombvector b2){
if(i==1)
	if(lvl->get_tile(yoffset/32,(offSet+32)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet+32, this->yoffset) != 1&&(p1.offSet/32 != (this->offSet+32)/32 || p1.yoffset/32 != this->yoffset/32 && p1.alive == 1) )
		return 1;
if(i==2)
	if(lvl->get_tile(yoffset/32,(offSet-32)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet-32, this->yoffset) != 1&&(p1.offSet/32 != (this->offSet-32)/32 || p1.yoffset/32 != this->yoffset/32 && p1.alive == 1) )
		return 1;
if(i==3)
	if(lvl->get_tile((yoffset-10)/32,(offSet)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet, this->yoffset-10) != 1&&(p1.offSet/32 != (this->offSet/32) || (p1.yoffset/32) != ((this->yoffset-10)/32) && p1.alive == 1))
		return 1;
if(i==4)
	if(lvl->get_tile((yoffset+33)/32,(offSet)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet, this->yoffset+33) != 1&&(p1.offSet/32 != this->offSet/32 || p1.yoffset/32 != (this->yoffset+33)/32 && p1.alive == 1) )
		return 1;
return 0;
}

int Foo::isalive(){
	return alive;

}
void Foo::handle_events()
{
	
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
		count++;
        //Set the velocity
        switch( event.key.keysym.sym )
        {
			
            case SDLK_RIGHT:velocity=FOO_WIDTH/8;keypressed=1;keyup=0; status=FOO_RIGHT; break;
            case SDLK_LEFT: velocity =-( FOO_WIDTH/8) ;keypressed=1;keyup=0; status=FOO_LEFT;break;
			case SDLK_UP: yvelocity=-(FOO_HEIGHT/8); keypressed=1;keyup=0;status=FOO_UP;break;
			case SDLK_DOWN: yvelocity =(FOO_HEIGHT/8); keypressed=1;keyup=0;status=FOO_DOWN; break;
			
		}
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
		
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT:velocity=velocity-((FOO_WIDTH/8)) ; keyup=1; count=0; keypressed=0; break;
            
			case SDLK_LEFT: velocity =velocity+(( FOO_WIDTH/8));keyup=1; count=0; keypressed=0; break;
			case SDLK_UP: yvelocity=yvelocity+((FOO_HEIGHT/8));keyup=1;count=0;keypressed=0; break;
			case SDLK_DOWN: yvelocity =yvelocity-((FOO_HEIGHT/8));keyup=1;count=0;keypressed=0; break;
        }
    }

printf("%d", keypressed);
}

int Foo::move(bombvector b, AIbombvector b2)
{
	
    //Move

	
	if(velocity&&yvelocity!=0)
		velocity=0;

    offSet += velocity;
	yoffset += yvelocity;
	
	
    //Keep the stick figure in bounds
    if( ( offSet< 32 ) || ( offSet + FOO_WIDTH>(21*32)))
    {
       
		offSet -= velocity;
		return 1;
	  }
//	else
	 if((yoffset<32)||(yoffset+ FOO_HEIGHT>21*32))
	 {
		 
		 yoffset -= yvelocity;
		return 1;
	 }
	 
	 if(status == FOO_UP&&yvelocity<0){		//CHECK MOVE UP
	//can't move through other players
		
		if(((c2.offSet/32) == (this->offSet/32) && (c2.yoffset/32) == ((this->yoffset+1)/32) && c2.alive == 1) || ((c1.offSet/32) == (this->offSet/32) && (c1.yoffset/32) ==((this->yoffset+1)/32) && c1.alive == 1) || ((c3.offSet/32)== (this->offSet/32) && (c3.yoffset/32) == ((this->yoffset+1)/32) && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		 if((lvl->get_tile(((yoffset+1)/32),((offSet)/32))!=GROUND))
		 {
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		 if(checkforBombs(&b,&b2,this->offSet, this->yoffset+1) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
	
	}
	if(status == FOO_DOWN&&yvelocity>0){		//CHECK MOVE DOWN
	//can't move through other players
		if((c2.offSet/32 == this->offSet/32 && c2.yoffset/32 == (this->yoffset+31)/32 && c2.alive == 1) || (c1.offSet/32 == this->offSet/32 && c1.yoffset/32 ==(this->yoffset+31)/32 && c1.alive == 1) || (c3.offSet/32== this->offSet/32 && c3.yoffset/32 == (this->yoffset+31)/32 && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		if((lvl->get_tile(((yoffset+FOO_HEIGHT-1)/32),((offSet)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,&b2,this->offSet, this->yoffset+FOO_HEIGHT-1) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
	}
	if(status == FOO_RIGHT&&velocity>0){		//CHECK MOVE RIGHT
	//can't move through other players
			if((c2.offSet/32 == (this->offSet+31)/32 && c2.yoffset/32 == this->yoffset/32 && c2.alive == 1) || (c1.offSet/32 == (this->offSet+31)/32 && c1.yoffset/32 ==this->yoffset/32 && c1.alive == 1) || (c3.offSet/32== (this->offSet+31)/32 && c3.yoffset/32 == this->yoffset/32 && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		if((lvl->get_tile(((yoffset)/32),((offSet+FOO_WIDTH-1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,&b2,this->offSet+FOO_WIDTH-1, this->yoffset) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
	}
	if(status == FOO_LEFT&&velocity<0){		//CHECK MOVE LEFT
	//can't move through other players
		if((c2.offSet/32 == (this->offSet+1)/32 && c2.yoffset/32 == this->yoffset/32 && c2.alive == 1) || (c1.offSet/32 == (this->offSet+1)/32 && c1.yoffset/32 ==this->yoffset/32 && c1.alive == 1) || (c3.offSet/32== (this->offSet+1)/32 && c3.yoffset/32 == this->yoffset/32 && c3.alive == 1))
		{		offSet-=velocity;
			 yoffset-=yvelocity;
		}
		 if((lvl->get_tile(((yoffset)/32),((offSet+1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
		else if(checkforBombs(&b,&b2,this->offSet+1, this->yoffset) == 1)
		{
			offSet-=velocity;
			yoffset-=yvelocity;
		 }
		
		
	}
}
	/*
	 if(status==FOO_RIGHT)
		 if((lvl->get_tile(((yoffset)/32),((offSet+FOO_WIDTH-1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
	if(status==FOO_LEFT)
		 if((lvl->get_tile(((yoffset)/32),((offSet+1)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
	if(status==FOO_UP)
		 if((lvl->get_tile(((yoffset+1)/32),((offSet)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }
	if(status==FOO_DOWN)
		 if((lvl->get_tile(((yoffset+FOO_HEIGHT-1)/32),((offSet)/32))!=GROUND)){
			 offSet-=velocity;
			 yoffset-=yvelocity;
		 }

}
*/
		 

	// else
	 /*
		 if((lvl->get_tile(((yoffset)/32),((offSet+FOO_WIDTH-1)/32))!=GROUND)||(lvl->get_tile(((yoffset)/32),(offSet)/32)!=GROUND)||(lvl->get_tile(((yoffset+FOO_HEIGHT-1)/32),(offSet+FOO_WIDTH-1)/32)!=GROUND)||((lvl->get_tile(((yoffset+FOO_HEIGHT-1)/32),((offSet)/32))!=GROUND)))
			 {
				 
			 offSet-=velocity;
			 yoffset-=yvelocity;
				 
				
		 }
}*/
		 /*
	if(((lvl->get_tile(((yoffset)/64),(offSet+FOO_WIDTH)/64)!=GROUND||lvl->get_tile(((yoffset+FOO_HEIGHT-3)/64),((offSet+FOO_WIDTH)/64)!=GROUND))&&status==FOO_RIGHT))
	{
		if(velocity>0)
		offSet -= velocity;
		if(velocity<0)
			offSet+=velocity;
		
	}
	else 
		if(((lvl->get_tile(((yoffset)/64),(offSet)/64)!=GROUND||lvl->get_tile(((yoffset+FOO_HEIGHT-4)/64),((offSet)/64)!=GROUND))&&status==FOO_LEFT))
	{
		if(velocity>0)
		offSet += velocity;
		if(velocity<0)
			offSet-=velocity;
		
	}
		else 
			if(((lvl->get_tile(((yoffset+FOO_HEIGHT)/64),(offSet)/64)!=GROUND||lvl->get_tile(((yoffset+FOO_HEIGHT)/64),(offSet+FOO_WIDTH-3)/64)!=GROUND))&&status==FOO_DOWN)
	{
		if(yvelocity>0)
		yoffset =yoffset- yvelocity;
		if(yvelocity<0)
			yoffset+=yvelocity;
		
	}
			else 
				if(((lvl->get_tile(((yoffset)/64),(offSet)/64)!=GROUND||lvl->get_tile(((yoffset)/64),(offSet+FOO_WIDTH-3)/64)!=GROUND))&&status==FOO_UP)
	{
		if(yvelocity>0)
		yoffset += yvelocity;
		if(yvelocity<0)
			yoffset-=yvelocity;
		
	}



}
*/
int frameToDraw=0;
int Foo::checkmove(int i, bombvector b, AIbombvector b2){
	if(i==1)
	if(lvl->get_tile(yoffset/32,(offSet+32)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet+32, this->yoffset) != 1&&(p1.offSet/32 != (this->offSet+32)/32 || p1.yoffset/32 != this->yoffset/32 && p1.alive == 1) )
		return 1;
if(i==2)
	if(lvl->get_tile(yoffset/32,(offSet-32)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet-32, this->yoffset) != 1&&(p1.offSet/32 != (this->offSet-32)/32 || p1.yoffset/32 != this->yoffset/32 && p1.alive == 1) )
		return 1;
if(i==3)
	if(lvl->get_tile((yoffset-10)/32,(offSet)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet, this->yoffset-10) != 1&&(p1.offSet/32 != (this->offSet/32) || (p1.yoffset/32) != ((this->yoffset-10)/32) && p1.alive == 1))
		return 1;
if(i==4)
	if(lvl->get_tile((yoffset+33)/32,(offSet)/32)==GROUND&&checkforBombs(&b,&b2,this->offSet, this->yoffset+33) != 1&&(p1.offSet/32 != this->offSet/32 || p1.yoffset/32 != (this->yoffset+33)/32 && p1.alive == 1) )
		return 1;
return 0;
}
void Foo::show()
{
	
	
	//bool isstill=true;
    //If Foo is moving left
    if( velocity < 0 )
    {
        //Set the animation to left
        status = FOO_LEFT;

        //Move to the next frame in the animation
        frame++;
    }
    //If Foo is moving right
    else if( velocity > 0 )
    {
        //Set the animation to right
        status = FOO_RIGHT;
		//isstill=false;
		//for( int i=0;i<4;i++) {
		//apply_surface( offSet+=16, yoffset, foo, screen, &clipsRight[ frame ] );
        //Move to the next frame in the animation
        //if(count%2==1)
		//SDL_Delay(200);
		//count++;
		//if(count==5){
		frame++;
		//count=0;
		//}
		//frameToDraw = ((SDL_GetTicks() - startTime) * animationRate / 1000) % animationLength;
		
		//counting++;
		//if(keypressed==true&&counting==40){
			//velocity-=(FOO_WIDTH/8);
			counting=0;
			//keypressed=false;
		//}
		
		//}
    }
	//If Foo is moving up
	else if(yvelocity<0)
	{
		 //Set the animation to up
		status = FOO_UP;
		//Move to the next frame in the animation
		frame++;
	}
	//If Foo is moving down
	else if (yvelocity>0)
	{
		//Set the animation to down
		status=FOO_DOWN;
		//Move to the next frame in the animation
		frame++;
		//frame = (SDL_GetTicks() / 500) % 4; 
		
		
	
	}
    //If Foo standing
    else
    {
        //Restart the animation
      
		frame = 0;
    }

    //Loop the animation
    if( frame >= 8 )
    {
       
		frame = 0;
    }

    //Show the stick figure
    if( status == FOO_RIGHT )
    {
	
		
		//frameToDraw = ((SDL_GetTicks() - startTime) * animationRate / 1000) % animationLength;
       
		apply_surface( offSet, yoffset, foo, screen, &clipsRight[ frame] );
		
	}
    else if( status == FOO_LEFT )
    {
        apply_surface( offSet, yoffset, foo, screen, &clipsLeft[ frame ] );
    }
	else if(status== FOO_UP)
	{
		 apply_surface( offSet, yoffset, foo, screen, &clipsUp[ frame ] );
	}
	else if (status == FOO_DOWN)
	{
		apply_surface( offSet, yoffset, foo, screen, &clipsDown[ frame ] );
	}

}
void spawn(bombvector b1, AIbombvector b2){

int c = 0;
	c1.randStart(22);
	c = c1.checkmove(1,b1,b2) + c1.checkmove(2,b1,b2) + c1.checkmove(3,b1,b2) + c1.checkmove(4,b1,b2);
	while(c < 2 || lvl->get_tile(c1.getyoffset()/32,c1.getoffset()/32) == BREAK || lvl->get_tile(c1.getyoffset()/32, c1.getoffset()/32) == SOLID){
		c=0;
		c1.randStart(22);
		c= c1.checkmove(1,b1,b2) + c1.checkmove(2,b1,b2) + c1.checkmove(3,b1,b2) + c1.checkmove(4,b1,b2);
	}
	c2.randStart(22);
	c=c2.checkmove(1,b1,b2) + c2.checkmove(2,b1,b2) + c2.checkmove(3,b1,b2) + c2.checkmove(4,b1,b2);
	while(c < 2 || lvl->get_tile(c2.getyoffset()/32,c2.getoffset()/32) == BREAK || lvl->get_tile(c2.getyoffset()/32,c2.getoffset()/32) == SOLID || (c1.getoffset()/32 == c2.getoffset()/32 && c1.getyoffset()/32 == c2.getyoffset()/32)){
		c=0;
		c2.randStart(22);
		c= c2.checkmove(1,b1,b2) + c2.checkmove(2,b1,b2) + c2.checkmove(3,b1,b2) + c2.checkmove(4,b1,b2);
	}
	c3.randStart(22);
	c3.checkmove(1,b1,b2) + c3.checkmove(2,b1,b2) + c3.checkmove(3,b1,b2) + c3.checkmove(4,b1,b2);
	while(c < 2  || lvl->get_tile(c3.getyoffset()/32,c3.getoffset()/32) == BREAK || lvl->get_tile(c3.getyoffset()/32,c3.getoffset()/32) == SOLID || (c1.getoffset()/32 == c3.getoffset()/32 && c1.getyoffset()/32 == c3.getyoffset()/32) || (c2.getoffset()/32 == c3.getoffset()/32 && c2.getyoffset()/32 == c3.getyoffset()/32)){
		c=0;
		c3.randStart(22);
		c=c3.checkmove(1,b1,b2) + c3.checkmove(2,b1,b2) + c3.checkmove(3,b1,b2) + c3.checkmove(4,b1,b2);
	}
	p1.randStart(22);
	c=p1.checkmove(1,b1,b2) + p1.checkmove(2,b1,b2) + p1.checkmove(3,b1,b2) + p1.checkmove(4,b1,b2);
	while(c < 2  || lvl->get_tile(p1.getyoffset()/32,p1.getoffset()/32) == BREAK || lvl->get_tile( p1.getyoffset()/32,p1.getoffset()/32) == SOLID || (c1.getoffset()/32 == p1.getoffset()/32 && c1.getyoffset()/32 == p1.getyoffset()/32) || (c2.getoffset()/32 == p1.getoffset()/32 && c2.getyoffset()/32 == p1.getyoffset()/32) || (c3.getoffset()/32 == p1.getoffset()/32 && c3.getyoffset()/32 == p1.getyoffset()/32)){
		c=0;
		p1.randStart(22);
		c= p1.checkmove(1,b1,b2) + p1.checkmove(2,b1,b2) + p1.checkmove(3,b1,b2) + p1.checkmove(4,b1,b2);
	}
	c1.name = "c1";
	c2.name = "c2";
	c3.name = "c3";
	//updateScores(0);



}

int main( int argc, char* args[] ) {
	
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

	
    bool quit = false;
	int animationRate = 12;
    int animationLength = 13;
    int startTime = SDL_GetTicks(); 

    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Split the dots", NULL );
    
    load_files();
	 set_clips();
	 Timer fps;
	
    int keyup=1;
    //Clip range for the top left
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = 32;
    clip[ 0 ].h = 32;
    
    //Clip range for the top right
    clip[ 1 ].x = 0;
    clip[ 1 ].y = 32;
    clip[ 1 ].w = 32;
    clip[ 1 ].h = 32;
    
    //Clip range for the bottom left
    clip[ 2 ].x = 0;
    clip[ 2 ].y = 64;
    clip[ 2 ].w = 32;
    clip[ 2 ].h = 32;
    
    /*
    //Clip range for the bottom right
    clip[ 3 ].x = 0;
    clip[ 3 ].y = 48;
    clip[ 3 ].w = 16;
    clip[ 3 ].h = 16;
    */

    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    //Apply the sprites to the screen
    /*
    apply_surface( 0, 0, dots, screen, &clip[ 0 ] );
    apply_surface( 540, 0, dots, screen, &clip[ 1 ] );
    apply_surface( 0, 380, dots, screen, &clip[ 2 ] );
    apply_surface( 540, 380, dots, screen, &clip[ 3 ] );
    */
   
    int test =0;
    lvl->generate();
    // c1.spawn();
	 
    //p1.spawn(); 
     bombvector bomb;
    AIbombvector AIbomb;
	spawn(bomb,AIbomb);
    //While the user hasn't quit
    while( quit == false )
	{
		//test++;
		fps.start();
        //While there's events to handle
        while( SDL_PollEvent( &event )||keypressed)
		{
			//test++;
			
			p1.handle_events();
			if(keypressed){
				test++;
				for(int i=0;i<40;i++){

					if(i%5==0){
					p1.move(bomb,AIbomb);
					c1.move(bomb,AIbomb);
					c2.move(bomb,AIbomb);
					}
					
				 if(i%10==0){
				 bomb.makebombs(p1);
				 AIbomb.makebombs(c1);
				  AIbomb.makebombs(c2);
				 }
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
	for(int i = 0; i < LEVEL_ROW; ++i) {
        for(int j = 0; j < LEVEL_COL; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 2 ] );

                printf("o");
            } else if(tile == SOLID) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 0 ] );

                printf("*");
            } else if(tile == BREAK) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 1 ] );

                printf("B");
            }
        }
        printf("\n");
    }
	p1.show();
	c1.show();
	c2.show();
	bomb.showbombs();
	AIbomb.showbombs();
	 
	  if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
      //  if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        //{
          //  SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        //}
		
		 //Cap the frame rate
       // if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        //{
         //   SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
       // }
				
				
				
				}
				if(p1.getoffset()%32!=0||p1.getyoffset()%32!=0){
					if(p1.velocity!=0&&(p1.offSet+4)%32==0)
					p1.offSet+=4;
					else
						if(p1.velocity!=0&&(p1.offSet-4)%32==0)
							p1.offSet-=4;
					
					if(p1.yvelocity!=0&&(p1.yoffset+4)%32==0)
							p1.yoffset+=4;
					else
						if(p1.yvelocity!=0&&(p1.yoffset-4)%32==0)
							p1.yoffset-=4;
				}
				
				
				//if(keypressed)
					//continue;
					
				//if(!keyup)
					//continue;
				
            //If the user has Xed out the window
            
			//if(!keyup)
			//	continue;
			
			}
		
		bomb.handle_events(p1);
		if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
		
		
		
		
		}
		if(c1.alive)
		c1.plantbomb(&AIbomb);
		if(c2.alive)
		c2.plantbomb(&AIbomb);
   if(!keypressed)
	   for(int i=0;i<40;i++){
  p1.move(bomb,AIbomb);
  if(i%5==0){
  c1.move(bomb,AIbomb);
  c2.move(bomb,AIbomb);
  }
  if(i%10==0){
   bomb.makebombs(p1);
   AIbomb.makebombs(c1);
   AIbomb.makebombs(c2);
  }
  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
	for(int i = 0; i < LEVEL_ROW; ++i) {
        for(int j = 0; j < LEVEL_COL; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 2 ] );

                printf("o");
            } else if(tile == SOLID) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 0 ] );

                printf("*");
            } else if(tile == BREAK) {
                apply_surface( i*32, j*32, dots, screen, &clip[ 1 ] );

                printf("B");
            }
        }
        printf("\n");
    }
	bomb.showbombs();
	AIbomb.showbombs();
	 p1.show();
	 c1.show();
	 c2.show();
	 if(p1.getoffset()%32!=0||p1.getyoffset()%32!=0)
					printf("dog");
	  if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
	   }
	   

}
	
    
    //Free the images and quit SDL
    clean_up();
    
    return 0;
    
}