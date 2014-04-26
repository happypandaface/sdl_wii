#include "controller.h"
#include "SDL/SDL.h"

#define CTRL_BIT_LEFT 1<<1
#define CTRL_BIT_RIGHT 1<<2
#define CTRL_BIT_QUIT 1<<3


long keysDown = 0;
SDL_Event event;

int controller_connected(int controller)
{
	// TODO: make this function
	return 0;
}
void controller_update()
{
		// scans if a button was pressed
        //        WPAD_ScanPads();
		//u32 held = WPAD_ButtonsHeld(0);
 
		// if the homebutton is pressed it will set done = true and it will fill the screen
		// with a black background
		//if(held & WPAD_BUTTON_HOME){
		//	done=true;
		//	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		//}
 
		// SDL_Flip refreshes the screen so it will show the updated screen
	while( SDL_PollEvent( &event ) ){
		switch( event.type ){
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RIGHT)
					keysDown |= CTRL_BIT_RIGHT;
				if (event.key.keysym.sym == SDLK_LEFT)
					keysDown |= CTRL_BIT_LEFT;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_RIGHT)
					keysDown &= ~CTRL_BIT_RIGHT;
				if (event.key.keysym.sym == SDLK_LEFT)
					keysDown &= ~CTRL_BIT_LEFT;
				break;
			case SDL_QUIT:
				keysDown |= CTRL_BIT_QUIT;
				break;
		}
	}
}
int key_down(int controller, int key)
{
	if (keysDown & CTRL_BIT_LEFT && key == CTRL_LEFT)
		return 1;
	if (keysDown & CTRL_BIT_RIGHT && key == CTRL_RIGHT)
		return 1;
	if (keysDown & CTRL_BIT_QUIT && key == CTRL_QUIT)
		return 1;
	return 0;
}