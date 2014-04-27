#include <SDL/sdl_image.h>

#include "res_loader.h"
//#include <math.h>

// images
#include "images/testSprite.h"
#include "images/dirtSquare.h"

ResourceLoader::ResourceLoader()
{
	for (int i = 0; i < NUM_IMAGES; ++i)
		images[i] = NULL;
}

ResourceLoader::~ResourceLoader()
{
	for (int i = 0; i < NUM_IMAGES; ++i)
		if (images[i] != NULL)
			delete images[i];
}

SDL_Surface *ResourceLoader::get_image(int image)
{
	// this loads c-image files
	if (image == IMG_TEST)
		return images[IMG_TEST_ARR];
	if (image == IMG_DIRT_SQUARE)
		return images[IMG_DIRT_SQUARE_ARR];
	return NULL;
}

float ResourceLoader::load()
{
	SDL_RWops * z1 = SDL_RWFromMem(testSprite,testSpriteSize);
	images[IMG_TEST_ARR] = IMG_LoadJPG_RW(z1);
	SDL_RWops * z2 = SDL_RWFromMem(dirtSquare,dirtSquareSize);
	images[IMG_DIRT_SQUARE_ARR] = IMG_LoadPNG_RW(z2);
	
	return 1.0f;
}