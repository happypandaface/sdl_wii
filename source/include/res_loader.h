#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include "SDL/SDL.h"

#define NUM_IMAGES 10

#define IMG_TEST 1
#define IMG_DIRT_SQUARE 2
#define IMG_COOL_GUY 3
#define IMG_COOL_GUY2 4
#define IMG_SPIKE_BALL1 5
#define IMG_SPIKE_BALL2 6
#define IMG_SPIKE_BALL3 7
#define IMG_SPIKE_BALL4 8
#define IMG_CAVE_BG 9
#define IMG_GIBLET1 10

class ResourceLoader
{
	public:
		ResourceLoader();
		~ResourceLoader();
		//SDL_Rect *get_src_rect(int image);
		void draw_image(int img_type, SDL_Surface *screen, float x, float y);
		float load();
	private:
		class ResImage;
		ResImage *get_image(int image);
		int get_arr_pos(int image);
		//SDL_Surface *imageFiles[NUM_FILES];
		ResImage *images[NUM_IMAGES];
		SDL_Rect *dst_rect;
};

#endif