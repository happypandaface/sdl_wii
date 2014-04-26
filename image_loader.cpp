
#include <SDL/sdl_image.h>

// images
#include "images/testSprite.h"


SDL_Surface *load_image(int image)
{
	// this loads c-image files
	SDL_RWops * z = SDL_RWFromMem(testSprite,testSpriteSize);
	return IMG_LoadJPG_RW(z);
}