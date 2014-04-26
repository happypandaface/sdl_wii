#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include <SDL/sdl.h>

#define IMG_TEST 1

	// because I can't get sdl_image 1.2 to work on the computer
	// I need to have wrapper functions for different function names
	// between sdl_image 1.2 and sdl_image2

SDL_Surface *load_image(int image);

#endif