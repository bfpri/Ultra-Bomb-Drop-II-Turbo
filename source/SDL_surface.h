#include "SDL.h"
#include"SDL_image.h"


SDL_Surface *foo = NULL;
SDL_Rect clipsRight[ 4 ];
SDL_Rect clipsLeft[ 4 ];
SDL_Rect clipsUp [4];
SDL_Rect clipsDown [4];
SDL_Event event;
SDL_Surface *screen = NULL;

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
