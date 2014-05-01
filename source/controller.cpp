#include "controller.h"
#include "SDL/SDL.h"

// wii libraries
#ifndef WINDOWS_BUILD
#include <gccore.h>
#include <wiiuse/wpad.h> 
#endif

#define CTRL_BIT_LEFT 0b00000001
#define CTRL_BIT_RIGHT 0b00000010
#define CTRL_BIT_QUIT 0b00000100
#define CTRL_BIT_UP 0b00001000
#define CTRL_BIT_DOWN 0b00010000
#define CTRL_BIT_2 0b00100000
#define CTRL_BIT_A 0b01000000

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
			if (event->type == SDL_KEYDOWN)
			{
				if (event->key.keysym.sym == SDLK_l)
					keysDown[0] |= CTRL_BIT_RIGHT;
				else if (event->key.keysym.sym == SDLK_j)
					keysDown[0] |= CTRL_BIT_LEFT;
				else if (event->key.keysym.sym == SDLK_i)
					keysDown[0] |= CTRL_BIT_UP;
				else if (event->key.keysym.sym == SDLK_k)
					keysDown[0] |= CTRL_BIT_DOWN;
				else if (event->key.keysym.sym == SDLK_h)
					keysDown[0] |= CTRL_BIT_2;
				else if (event->key.keysym.sym == SDLK_n)
					keysDown[0] |= CTRL_BIT_A;
				else if (event->key.keysym.sym == SDLK_d)
					keysDown[1] |= CTRL_BIT_RIGHT;
				else if (event->key.keysym.sym == SDLK_a)
					keysDown[1] |= CTRL_BIT_LEFT;
				else if (event->key.keysym.sym == SDLK_w)
					keysDown[1] |= CTRL_BIT_UP;
				else if (event->key.keysym.sym == SDLK_s)
					keysDown[1] |= CTRL_BIT_DOWN;
				else if (event->key.keysym.sym == SDLK_f)
					keysDown[1] |= CTRL_BIT_2;
				else if (event->key.keysym.sym == SDLK_c)
					keysDown[1] |= CTRL_BIT_A;
			}else if (event->type == SDL_KEYUP)
			{
				if (event->key.keysym.sym == SDLK_l)
					keysDown[0] &= ~CTRL_BIT_RIGHT;
				else if (event->key.keysym.sym == SDLK_j)
					keysDown[0] &= ~CTRL_BIT_LEFT;
				else if (event->key.keysym.sym == SDLK_i)
					keysDown[0] &= ~CTRL_BIT_UP;
				else if (event->key.keysym.sym == SDLK_k)
					keysDown[0] &= ~CTRL_BIT_DOWN;
				else if (event->key.keysym.sym == SDLK_h)
					keysDown[0] &= ~CTRL_BIT_2;
				else if (event->key.keysym.sym == SDLK_n)
					keysDown[0] &= ~CTRL_BIT_A;
				else if (event->key.keysym.sym == SDLK_d)
					keysDown[1] &= ~CTRL_BIT_RIGHT;
				else if (event->key.keysym.sym == SDLK_a)
					keysDown[1] &= ~CTRL_BIT_LEFT;
				else if (event->key.keysym.sym == SDLK_w)
					keysDown[1] &= ~CTRL_BIT_UP;
				else if (event->key.keysym.sym == SDLK_s)
					keysDown[1] &= ~CTRL_BIT_DOWN;
				else if (event->key.keysym.sym == SDLK_f)
					keysDown[1] &= ~CTRL_BIT_2;
				else if (event->key.keysym.sym == SDLK_c)
					keysDown[1] &= ~CTRL_BIT_A;
			}else if (event->type == SDL_QUIT)
			{
				keysDown[0] |= CTRL_BIT_QUIT;
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
			if(held & WPAD_BUTTON_A)
				keysDown[i] |= CTRL_BIT_A;
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
	if (keysDown[controller] & CTRL_BIT_A && key == CTRL_A)
		return 1;
	return 0;
}