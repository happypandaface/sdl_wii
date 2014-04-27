#include "controller.h"
#include "SDL/SDL.h"

// wii libraries
#ifndef WINDOWS_BUILD
#include <gccore.h>
#include <wiiuse/wpad.h> 
#endif

#define CTRL_BIT_LEFT 1<<1
#define CTRL_BIT_RIGHT 1<<2
#define CTRL_BIT_QUIT 1<<3
#define CTRL_BIT_UP 1<<4
#define CTRL_BIT_DOWN 1<<5
#define CTRL_BIT_2 1<<6

Controller::Controller()
{
	event = new SDL_Event();
	for (int i = 0; i < NUM_CONTROLLERS; ++i)
		keysDown[i] = 0;
}

Controller::~Controller()
{
	delete event;
}

int Controller::controller_connected(int controller)
{
	// TODO: make this function
	return 0;
}
void Controller::update()
{
	// use ifdefs here and -D on the command line to
	// choose building for wii or building for windows
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
	#ifdef WINDOWS_BUILD
		while( SDL_PollEvent( event ) ){
			switch( event->type ){
				case SDL_KEYDOWN:
					if (event->key.keysym.sym == SDLK_RIGHT)
						keysDown[0] |= CTRL_BIT_RIGHT;
					else if (event->key.keysym.sym == SDLK_LEFT)
						keysDown[0] |= CTRL_BIT_LEFT;
					else if (event->key.keysym.sym == SDLK_UP)
						keysDown[0] |= CTRL_BIT_UP;
					else if (event->key.keysym.sym == SDLK_DOWN)
						keysDown[0] |= CTRL_BIT_DOWN;
					break;
				case SDL_KEYUP:
					if (event->key.keysym.sym == SDLK_RIGHT)
						keysDown[0] &= ~CTRL_BIT_RIGHT;
					else if (event->key.keysym.sym == SDLK_LEFT)
						keysDown[0] &= ~CTRL_BIT_LEFT;
					else if (event->key.keysym.sym == SDLK_UP)
						keysDown[0] &= ~CTRL_BIT_UP;
					else if (event->key.keysym.sym == SDLK_DOWN)
						keysDown[0] &= ~CTRL_BIT_DOWN;
					break;
				case SDL_QUIT:
					keysDown[0] |= CTRL_BIT_QUIT;
					break;
			}
		}
	#else
		WPAD_ScanPads();
		for (int i = 0; i < NUM_CONTROLLERS; ++i)
		{
			u32 held = WPAD_ButtonsHeld(i);
			keysDown[i] = 0;
			if(held & WPAD_BUTTON_UP)
				keysDown[i] |= CTRL_BIT_LEFT;
			if(held & WPAD_BUTTON_DOWN)
				keysDown[i] |= CTRL_BIT_RIGHT;
			if(held & WPAD_BUTTON_RIGHT)
				keysDown[i] |= CTRL_BIT_UP;
			if(held & WPAD_BUTTON_LEFT)
				keysDown[i] |= CTRL_BIT_DOWN;
			if(held & WPAD_BUTTON_2)
				keysDown[i] |= CTRL_BIT_2;
		}
	#endif
}

int Controller::key_down(int controller, int key)
{
	if (keysDown[controller] & CTRL_BIT_LEFT && key == CTRL_LEFT)
		return 1;
	if (keysDown[controller] & CTRL_BIT_RIGHT && key == CTRL_RIGHT)
		return 1;
	if (keysDown[controller] & CTRL_BIT_UP && key == CTRL_UP)
		return 1;
	if (keysDown[controller] & CTRL_BIT_DOWN && key == CTRL_DOWN)
		return 1;
	if (keysDown[controller] & CTRL_BIT_QUIT && key == CTRL_QUIT)
		return 1;
	if (keysDown[controller] & CTRL_BIT_2 && key == CTRL_2)
		return 1;
	return 0;
}