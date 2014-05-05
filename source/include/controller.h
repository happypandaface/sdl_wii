#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL/SDL.h"

#define CTRL_LEFT 1
#define CTRL_RIGHT 2
#define CTRL_QUIT 3
#define CTRL_UP 4
#define CTRL_DOWN 5
#define CTRL_2 6
#define CTRL_A 7
#define CTRL_1 8
#define CTRL_MINUS 9

#define NUM_CONTROLLERS 4

class Controller
{
	public:
		Controller();
		~Controller();
		int controller_connected(int controller);
		void update();
		int key_down(int controller, int key);
		int eat_key(int controller, int key);
	private:
		long keysDown[NUM_CONTROLLERS];
		SDL_Event *event;
};

#endif