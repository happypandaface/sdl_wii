#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include <SDL/sdl.h>

#define NUM_IMAGES 2

#define IMG_TEST 1
#define IMG_TEST_ARR 0
#define IMG_DIRT_SQUARE 2
#define IMG_DIRT_SQUARE_ARR 1

class ResourceLoader
{
	public:
		ResourceLoader();
		~ResourceLoader();
		SDL_Surface *get_image(int image);
		float load();
	private:
		SDL_Surface *images[NUM_IMAGES];
};

#endif