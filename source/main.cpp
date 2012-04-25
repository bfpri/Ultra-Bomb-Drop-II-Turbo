#include "SDL.h"
#include "SDL_image.h"

#include <stdio.h>
#include <string>
#include "Timer.h"


#include "Level.h"

using namespace std;
//The frames per second
const int FRAMES_PER_SECOND = 10;

//The direction status of the bomberman figure
const int FOO_RIGHT = 0;
const int FOO_LEFT = 1;
const int FOO_UP = 3;
const int FOO_DOWN =4;

#define COLORKEY 255, 0, 255

//The surfaces
SDL_Surface *bomb=NULL;
SDL_Surface *foo = NULL;
SDL_Surface *dots = NULL;
SDL_Surface *screen = NULL;
int alpha = SDL_ALPHA_OPAQUE;
//The dimenstions of the bomberman figure
const int FOO_WIDTH = 48;
const int FOO_HEIGHT = 58;

const int BOMB_WIDTH= 27;
const int BOMB_HEIGHT=27;
//The event structure
SDL_Event event;

 Level* lvl = new Level();
//The portions of the sprite map to be blitted
SDL_Rect clip[ 4 ];
SDL_Rect bombclip[4];
//The areas of the sprite sheet
SDL_Rect clipsRight[ 4 ];
SDL_Rect clipsLeft[ 4 ];
SDL_Rect clipsUp [4];
SDL_Rect clipsDown [4];

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
    dots = load_image( "tiles1.gif" );
	 
      
    //If there was an problem loading the sprite map
    if( dots == NULL )
    {
        return false;
    }
	//foo = ImgLoader( "costume2.gif" ,1,255,255,255,0);
	//foo = ImgLoader( "costume2.gif" ,1);
	foo=load_image("costume3.gif");
	if( foo == NULL )
    {
        return false;
    }
    bomb=load_image("BMLT.gif");
	if( bomb == NULL )
    {
        return false;
    }
    //If eveything loaded fine
    return true;
}

bool quit = false;
void set_clips()
{
    //Clip the sprites
    clipsRight[ 0 ].x = 0;
    clipsRight[ 0 ].y = 179;
    clipsRight[ 0 ].w = FOO_WIDTH;
    clipsRight[ 0 ].h = FOO_HEIGHT;

    clipsRight[ 1 ].x = FOO_WIDTH;
    clipsRight[ 1 ].y = 179;
    clipsRight[ 1 ].w = FOO_WIDTH;
    clipsRight[ 1 ].h = FOO_HEIGHT;

    clipsRight[ 2 ].x = FOO_WIDTH * 2;
    clipsRight[ 2 ].y = 179;
    clipsRight[ 2 ].w = FOO_WIDTH;
    clipsRight[ 2 ].h = FOO_HEIGHT;

    clipsRight[ 3 ].x = FOO_WIDTH * 3;
    clipsRight[ 3 ].y = 179;
    clipsRight[ 3 ].w = FOO_WIDTH;
    clipsRight[ 3 ].h = FOO_HEIGHT;

    clipsLeft[ 0 ].x = 0;
    clipsLeft[ 0 ].y = FOO_HEIGHT;
    clipsLeft[ 0 ].w = FOO_WIDTH;
    clipsLeft[ 0 ].h = FOO_HEIGHT;

    clipsLeft[ 1 ].x = FOO_WIDTH;
    clipsLeft[ 1 ].y = FOO_HEIGHT;
    clipsLeft[ 1 ].w = FOO_WIDTH;
    clipsLeft[ 1 ].h = FOO_HEIGHT;

    clipsLeft[ 2 ].x = FOO_WIDTH * 2;
    clipsLeft[ 2 ].y = FOO_HEIGHT;
    clipsLeft[ 2 ].w = FOO_WIDTH;
    clipsLeft[ 2 ].h = FOO_HEIGHT;

    clipsLeft[ 3 ].x = FOO_WIDTH * 3;
    clipsLeft[ 3 ].y = FOO_HEIGHT;
    clipsLeft[ 3 ].w = FOO_WIDTH;
    clipsLeft[ 3 ].h = FOO_HEIGHT;

	clipsUp[0].x=0;
	clipsUp[0].y=123;
	clipsUp[ 0 ].w = FOO_WIDTH;
    clipsUp[ 0 ].h = FOO_HEIGHT;

	clipsUp[ 1 ].x = FOO_WIDTH;
    clipsUp[ 1 ].y = 123;
    clipsUp[ 1 ].w = FOO_WIDTH;
    clipsUp[ 1 ].h = FOO_HEIGHT;

    clipsUp[ 2 ].x = FOO_WIDTH * 2;
    clipsUp[ 2 ].y = 123;
    clipsUp[ 2 ].w = FOO_WIDTH;
    clipsUp[ 2 ].h = FOO_HEIGHT;

    clipsUp[ 3 ].x = FOO_WIDTH * 3;
    clipsUp[ 3 ].y = 123;
    clipsUp[ 3 ].w = FOO_WIDTH;
    clipsUp[ 3 ].h = FOO_HEIGHT;

	clipsDown[0].x=0;
	clipsDown[0].y=0;
	clipsDown[ 0 ].w = FOO_WIDTH;
    clipsDown[ 0 ].h = FOO_HEIGHT;

	clipsDown[ 1 ].x = FOO_WIDTH;
    clipsDown[ 1 ].y = 0;
    clipsDown[ 1 ].w = FOO_WIDTH;
    clipsDown[ 1 ].h = FOO_HEIGHT;

    clipsDown[ 2 ].x = FOO_WIDTH * 2;
    clipsDown[ 2 ].y = 0;
    clipsDown[ 2 ].w = FOO_WIDTH;
    clipsDown[ 2 ].h = FOO_HEIGHT;

    clipsDown[ 3 ].x = FOO_WIDTH * 3;
    clipsDown[ 3 ].y = 0;
    clipsDown[ 3 ].w = FOO_WIDTH;
    clipsDown[ 3 ].h = FOO_HEIGHT;


	bombclip[0].x=387;
	bombclip[0].y=49;
	bombclip[ 0 ].w = BOMB_WIDTH;
    bombclip[ 0 ].h = BOMB_HEIGHT;

	bombclip[ 1 ].x = 387+BOMB_WIDTH;
    bombclip[ 1 ].y = 49;
    bombclip[ 1 ].w = BOMB_WIDTH;
    bombclip[ 1 ].h = BOMB_HEIGHT;

    bombclip[ 2 ].x = 387+BOMB_WIDTH * 2;
    bombclip[ 2 ].y = 49;
    bombclip[ 2 ].w = BOMB_WIDTH;
    bombclip[ 2 ].h = BOMB_HEIGHT;
	
	bombclip[ 3 ].x = 412;
    bombclip[ 3 ].y = 108;
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

class Foo
{

protected:
    //The offset
    int offSet;
	int yoffset;
    //Its rate of movement
    int velocity;
	int yvelocity;
    //Its current frame
    int frame;
	
    //Its animation status
    int status;
	
    public:
		int getstatus();
		int getoffset();
	int getyoffset();
    //Initializes the variables
    Foo();
	void makebomb();
    //Handles input
    void handle_events();

    //Moves the stick figure
    int move();

    //Shows the stick figure
    void show();
};
int Foo::getstatus(){
return status;
}
int Foo::getoffset(){
return offSet;
}
int Foo::getyoffset(){
return yoffset;
}
Foo::Foo()
{
    //Initialize movement variables
    offSet = 0;
    velocity = 0;
	bool flag=false;
	for(int i = 1; i < LEVEL_ROW-1; ++i) {
        for(int j = 1; j < LEVEL_COL-1; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND&&(lvl->get_tile(j+1,i)==GROUND||lvl->get_tile(j-1,i)==GROUND||lvl->get_tile(j,i+1)==GROUND||lvl->get_tile(j,i-1)==GROUND)) {
                
				offSet=i*64;
				yoffset=j*64;
              flag=true;
				break;
            } 
        }
        if(flag)
			break;
		printf("\n");
    }

	//yoffset=SCREEN_HEIGHT-FOO_HEIGHT;
	yvelocity=0;
    //Initialize animation variables
    frame = 0;
    status = FOO_RIGHT;
}

class Bomb:public Foo
{
private:
	int offSet;
	int yoffset;
	int frame;
	int spacepressed;
	int counter;
public: void makebomb(Foo foo);
		Bomb();
		void handle_events();
		void showbomb();



};
 Bomb::Bomb(){
offSet=Foo::offSet;
yoffset=0;
frame=0;
spacepressed=0;
counter=0;
}

void Bomb::makebomb( Foo foo){
	counter++;
	if(counter==1){
	if( foo.getstatus() == FOO_RIGHT )
    {
        offSet=foo.getoffset()+FOO_WIDTH;
		yoffset=foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2;
	
    }
    else if( foo.getstatus() == FOO_LEFT )
    {
		offSet=foo.getoffset()-10;
		yoffset=foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2;
     
    }
	else if(foo.getstatus()== FOO_UP)
	{
		offSet=foo.getoffset()+15;
		yoffset=foo.getyoffset()-BOMB_HEIGHT-2;
		
	}
	else if (foo.getstatus() == FOO_DOWN)
	{
		offSet=foo.getoffset()+15;
		yoffset=foo.getyoffset()+FOO_HEIGHT+2;
		
	}
	}
	


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
void Foo::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity += FOO_WIDTH / 4;status=FOO_RIGHT; break;
            case SDLK_LEFT: velocity -= FOO_WIDTH /4; status=FOO_LEFT;break;
			case SDLK_UP: yvelocity-=FOO_HEIGHT/4; status=FOO_UP;break;
			case SDLK_DOWN: yvelocity +=FOO_HEIGHT/4; status=FOO_DOWN; break;
			
		}
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity -= FOO_WIDTH / 4; break;
            case SDLK_LEFT: velocity += FOO_WIDTH / 4; break;
			case SDLK_UP: yvelocity+=FOO_HEIGHT/4; break;
			case SDLK_DOWN: yvelocity -=FOO_HEIGHT/4; break;
        }
    }
}

int Foo::move()
{
    //Move
	if(status==FOO_DOWN)
	printf("yoffset %d");
    offSet += velocity;
	yoffset += yvelocity;
    //Keep the stick figure in bounds
    if( ( offSet+2< 64 ) || ( offSet + FOO_WIDTH-2>(10*64)))
    {
       
		offSet -= velocity;
		return 1;
	  }
//	else
	 if((yoffset+2<64)||(yoffset -2+ FOO_HEIGHT>10*64))
	 {
		 
		 yoffset -= yvelocity;
		return 1;
	 }
	// else
		 if((lvl->get_tile(((yoffset+6)/64),((offSet+FOO_WIDTH-4)/64))!=GROUND)||(lvl->get_tile(((yoffset+6)/64),(offSet+6)/64)!=GROUND)||(lvl->get_tile(((yoffset+FOO_HEIGHT-4)/64),(offSet+FOO_WIDTH-4)/64)!=GROUND)||((lvl->get_tile(((yoffset+FOO_HEIGHT-4)/64),((offSet+6)/64))!=GROUND)))
			 {
				 
			 offSet-=velocity;
			 yoffset-=yvelocity;
				 
				
		 }
}
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

void Foo::show()
{
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

        //Move to the next frame in the animation
        frame++;
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

	
	}
    //If Foo standing
    else
    {
        //Restart the animation
        frame = 0;
    }

    //Loop the animation
    if( frame >= 4 )
    {
        frame = 0;
    }

    //Show the stick figure
    if( status == FOO_RIGHT )
    {
        apply_surface( offSet, yoffset, foo, screen, &clipsRight[ frame ] );
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
class bombvector
{
	vector<Bomb> bombvect;
public:
	void handle_events(Foo foo);
	void makebombs(Foo foo);
	void showbombs();
};
void bombvector::makebombs(Foo foo){
	for(int i=0;i<bombvect.size();i++)
	bombvect[i].makebomb(foo);
}
void bombvector::showbombs(){
	for(int i=0;i<bombvect.size();i++)
	bombvect[i].showbomb();
}
void bombvector::handle_events(Foo foo){
	if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        if( event.key.keysym.sym==SDLK_SPACE ){
        
            Bomb bomb;
			if(foo.getstatus()==FOO_RIGHT&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2)/64,(foo.getoffset()+FOO_WIDTH+BOMB_WIDTH)/64)==GROUND&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-5)/64,(foo.getoffset()+FOO_WIDTH+BOMB_WIDTH)/64)==GROUND)
			bombvect.push_back(bomb); 
			if(foo.getstatus()==FOO_LEFT&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT-BOMB_HEIGHT+2)/64,(foo.getoffset()-(BOMB_WIDTH-10))/64)==GROUND&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT)/64,(foo.getoffset()-(BOMB_WIDTH-10))/64)==GROUND)
			bombvect.push_back(bomb); 
			if(foo.getstatus()==FOO_UP&&lvl->get_tile((foo.getyoffset()-BOMB_HEIGHT-2)/64,((foo.getoffset()+15)/64))==GROUND&&lvl->get_tile((foo.getyoffset()-BOMB_HEIGHT-2)/64,((foo.getoffset()+15+BOMB_WIDTH)/64))==GROUND)
			bombvect.push_back(bomb); 
			if(foo.getstatus()==FOO_DOWN&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT+2+BOMB_HEIGHT)/64,(foo.getoffset()+15)/64)==GROUND&&lvl->get_tile((foo.getyoffset()+FOO_HEIGHT+2+BOMB_HEIGHT)/64,(foo.getoffset()+15+BOMB_WIDTH)/64)==GROUND)
			bombvect.push_back(bomb); 

		}
		
    }
}

int main( int argc, char* args[] ) {
	
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
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
	
    
    //Clip range for the top left
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = 64;
    clip[ 0 ].h = 64;
    
    //Clip range for the top right
    clip[ 1 ].x = 0;
    clip[ 1 ].y = 64;
    clip[ 1 ].w = 64;
    clip[ 1 ].h = 64;
    
    //Clip range for the bottom left
    clip[ 2 ].x = 0;
    clip[ 2 ].y = 128;
    clip[ 2 ].w = 64;
    clip[ 2 ].h = 64;
    
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
   
    
    lvl->generate();
    
	 Foo walk;
     
     bombvector bomb;
    
    //While the user hasn't quit
    while( quit == false )
	{
		fps.start();
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
		{
			walk.handle_events();
			bomb.handle_events(walk);
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
		
   walk.move();
  
   bomb.makebombs(walk);
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
	for(int i = 0; i < LEVEL_ROW; ++i) {
        for(int j = 0; j < LEVEL_COL; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND) {
                apply_surface( i*64, j*64, dots, screen, &clip[ 2 ] );

                printf("o");
            } else if(tile == SOLID) {
                apply_surface( i*64, j*64, dots, screen, &clip[ 0 ] );

                printf("*");
            } else if(tile == BREAK) {
                apply_surface( i*64, j*64, dots, screen, &clip[ 1 ] );

                printf("B");
            }
        }
        printf("\n");
    }
	bomb.showbombs();
	 walk.show();
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
	
    
    //Free the images and quit SDL
    clean_up();
    
    return 0;
    
}