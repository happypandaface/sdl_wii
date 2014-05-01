#ifndef _IMAGE_LOADER_H
#define _IMAGE_LOADER_H

#include "SDL/SDL.h"
#include "image_effect.h"

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
#define IMG_STONE_EMBLEM1 11
#define IMG_STONE_EMBLEM2 12
#define IMG_STONE_EMBLEM3 13
#define IMG_STONE_EMBLEM4 14
#define IMG_WALL_GUN 15
#define IMG_DIRT_SQUARE_NORTH 16
#define IMG_DIRT_SQUARE_SOUTH 17
#define IMG_DIRT_SQUARE_EAST 18
#define IMG_DIRT_SQUARE_WEST 19
#define IMG_PLR_INDCTR_1 20
#define IMG_PLR_INDCTR_2 21
#define IMG_PLR_INDCTR_3 22
#define IMG_PLR_INDCTR_4 23
#define IMG_BLUE_LAZER_1 24
#define IMG_BLUE_LAZER_2 25
#define IMG_BLUE_LAZER_3 26
#define IMG_COOL_GUY_WALK_RIGHT_1 27
#define IMG_COOL_GUY_WALK_RIGHT_2 28
#define IMG_COOL_GUY_WALK_LEFT_1 29
#define IMG_COOL_GUY_WALK_LEFT_2 30
#define IMG_COOL_GUY_STAND_LEFT 31
#define IMG_COOL_GUY_STAND_RIGHT 32
#define IMG_RED_LAZER_1 33
#define IMG_RED_LAZER_2 34
#define IMG_RED_LAZER_3 35
#define IMG_FINISH_LEVEL_1 36
#define IMG_FINISH_LEVEL_2 37
#define IMG_FINISH_LEVEL_3 38
#define IMG_FINISH_LEVEL_4 39
#define IMG_FINISH_LEVEL_5 40
#define IMG_FINISH_LEVEL_6 41
#define IMG_FINISH_LEVEL_7 42
#define IMG_FINISH_LEVEL_8 43

#define NUM_IMAGES 43 // this should be the num of the last IMG_

class ResourceLoader
{
	public:
		ResourceLoader();
		~ResourceLoader();
		//SDL_Rect *get_src_rect(int image);
		void draw_image(int img_type, SDL_Surface *screen, float x, float y);
		void draw_image(int img_type, SDL_Surface *screen, float x, float y, ImageEffect **effects, int effects_size);
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