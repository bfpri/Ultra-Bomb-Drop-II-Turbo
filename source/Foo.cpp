#include "Foo.h"
#include "SDL.h"
#include "SDL_image.h"

const int FOO_RIGHT = 0;
const int FOO_LEFT = 1;
const int FOO_UP = 3;
const int FOO_DOWN =4;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int FOO_WIDTH = 32;
const int FOO_HEIGHT = 39;






Foo::Foo()
{
    //Initialize movement variables
    offSet = 0;
    velocity = 0;
	yoffset=SCREEN_HEIGHT-FOO_HEIGHT;
	yvelocity=0;
    //Initialize animation variables
    frame = 0;
    status = FOO_RIGHT;
}

void Foo::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity += FOO_WIDTH / 4; break;
            case SDLK_LEFT: velocity -= FOO_WIDTH / 4; break;
			case SDLK_UP: yvelocity-=FOO_HEIGHT/4; break;
			case SDLK_DOWN: yvelocity +=FOO_HEIGHT/4; break;
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

void Foo::move()
{
    //Move
    offSet += velocity;
	yoffset += yvelocity;
    //Keep the stick figure in bounds
    if( ( offSet < 0 ) || ( offSet + FOO_WIDTH > SCREEN_WIDTH ))
    {
        offSet -= velocity;
	  }
	 if((yoffset<0)||(yoffset + FOO_HEIGHT>SCREEN_HEIGHT))
	 {
		 yoffset -= yvelocity;
	 }
}

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