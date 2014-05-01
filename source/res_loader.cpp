#include <SDL/sdl_image.h>

#include "res_loader.h"
//#include <math.h>

// images
#include "images/testSprite.h"
#include "images/dirtSquare.h"
#include "images/coolGuy.h"
#include "images/spikeBall.h"
#include "images/caveStory.h"
#include "images/giblet.h"
#include "images/stoneEmblemSheet.h"
#include "images/wallGun.h"
#include "images/playerIndicator.h"
#include "images/blueLazer.h"
#include "images/finishLevel.h"

class ResourceLoader::ResImage
{
	public:
		ResImage(int in, SDL_Surface* s, float x, float y, float w, float h)
		{
			img_num = in;
			img_file = s;
			src_rect = new SDL_Rect;
			src_rect->x = x;
			src_rect->y = y;
			src_rect->w = w;
			src_rect->h = h;
		}
		~ResImage()
		{
			delete src_rect;
		}
		SDL_Rect *getSrcRect()
		{
			return src_rect;
		}
		int getImgNum()
		{
			return img_num;
		}
		SDL_Surface *getImgFile()
		{
			return img_file;
		}
	private:
		int img_num;
		SDL_Surface *img_file;
		SDL_Rect *src_rect;
};

ResourceLoader::ResourceLoader()
{
	for (int i = 0; i < NUM_IMAGES; ++i)
		images[i] = NULL;
	//for (int i = 0; i < NUM_FILES; ++i)
	//	imageFiles[i] = NULL;
	dst_rect = new SDL_Rect;
	dst_rect->x = 0;
	dst_rect->y = 0;
	dst_rect->w = 64;
	dst_rect->h = 64;
}

ResourceLoader::~ResourceLoader()
{
	//for (int i = 0; i < NUM_FILES; ++i)
	//	if (imageFiles[i] != NULL)
	//		delete imageFiles[i];
	for (int i = 0; i < NUM_IMAGES; ++i)
		if (images[i] != NULL)
			delete images[i];
	delete dst_rect;
}

/*
SDL_Surface *ResourceLoader::get_image(int image)
{
	// this loads c-image files
	if (image == IMG_TEST)
		return imageFiles[IMG_TEST_ARR];
	if (image == IMG_DIRT_SQUARE)
		return imageFiles[IMG_DIRT_SQUARE_ARR];
	if (image == IMG_COOL_GUY)
		return imageFiles[IMG_COOL_GUY_ARR];
	if (image == IMG_COOL_GUY2)
		return imageFiles[IMG_COOL_GUY2_ARR];
	return NULL;
}*/

ResourceLoader::ResImage *ResourceLoader::get_image(int image)
{
	return images[get_arr_pos(image)];
}

int ResourceLoader::get_arr_pos(int image)
{
	// put some special cases in here
	return image-1;
}

float ResourceLoader::load()
{
	SDL_RWops * flowerFile = SDL_RWFromMem(testSprite,testSpriteSize);
	SDL_Surface *flowerSurf = IMG_LoadJPG_RW(flowerFile);
	
	SDL_RWops * dirtFile = SDL_RWFromMem(dirtSquareData,dirtSquareSize);
	SDL_Surface *dirtSurf = IMG_LoadPNG_RW(dirtFile);
	
	SDL_RWops * coolGuyFile = SDL_RWFromMem(coolGuy,coolGuySize);
	SDL_Surface *coolGuySurf = IMG_LoadPNG_RW(coolGuyFile);
	
	SDL_RWops * spikeBallFile = SDL_RWFromMem(spikeBallData,spikeBallSize);
	SDL_Surface *spikeBallSurf = IMG_LoadPNG_RW(spikeBallFile);
	
	SDL_RWops * caveStoryFile = SDL_RWFromMem(caveStoryData,caveStorySize);
	SDL_Surface *caveStorySurf = IMG_LoadPNG_RW(caveStoryFile);
	
	SDL_RWops * gibletFile = SDL_RWFromMem(gibletData,gibletSize);
	SDL_Surface *gibletSurf = IMG_LoadPNG_RW(gibletFile);
	
	SDL_RWops * stoneEmblemFile = SDL_RWFromMem(stoneEmblemData,stoneEmblemSize);
	SDL_Surface *stoneEmblemSurf = IMG_LoadPNG_RW(stoneEmblemFile);
	
	SDL_RWops * wallGunFile = SDL_RWFromMem(wallGunData,wallGunSize);
	SDL_Surface *wallGunSurf = IMG_LoadPNG_RW(wallGunFile);
	
	SDL_RWops * plrIndctrFile = SDL_RWFromMem(playerIndicatorData,playerIndicatorSize);
	SDL_Surface *plrIndctrSurf = IMG_LoadPNG_RW(plrIndctrFile);
	
	SDL_RWops * blueLazerFile = SDL_RWFromMem(blueLazerData,blueLazerSize);
	SDL_Surface *blueLazerSurf = IMG_LoadPNG_RW(blueLazerFile);
	
	SDL_RWops * finishLevelFile = SDL_RWFromMem(finishLevelData,finishLevelSize);
	SDL_Surface *finishLevelSurf = IMG_LoadPNG_RW(finishLevelFile);
	
	images[get_arr_pos(IMG_TEST)] = new ResourceLoader::ResImage(
		IMG_TEST, flowerSurf,
		0, 0, 64, 64);
	images[get_arr_pos(IMG_DIRT_SQUARE)] = new ResourceLoader::ResImage(
		IMG_DIRT_SQUARE, dirtSurf,
		0, 0, 64, 64);
	images[get_arr_pos(IMG_DIRT_SQUARE_NORTH)] = new ResourceLoader::ResImage(
		IMG_DIRT_SQUARE_NORTH, dirtSurf,
		64*2, 0, 64, 64);
	images[get_arr_pos(IMG_DIRT_SQUARE_SOUTH)] = new ResourceLoader::ResImage(
		IMG_DIRT_SQUARE_SOUTH, dirtSurf,
		64*3, 0, 64, 64);
	images[get_arr_pos(IMG_DIRT_SQUARE_EAST)] = new ResourceLoader::ResImage(
		IMG_DIRT_SQUARE_EAST, dirtSurf,
		64*4, 0, 64, 64);
	images[get_arr_pos(IMG_DIRT_SQUARE_WEST)] = new ResourceLoader::ResImage(
		IMG_DIRT_SQUARE_WEST, dirtSurf,
		64*1, 0, 64, 64);
	images[get_arr_pos(IMG_COOL_GUY)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY, coolGuySurf,
		20, 10, 33, 76);
	images[get_arr_pos(IMG_COOL_GUY2)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY2, coolGuySurf,
		62, 174, 30, 72);
	images[get_arr_pos(IMG_SPIKE_BALL1)] = new ResourceLoader::ResImage(
		IMG_SPIKE_BALL1, spikeBallSurf,
		0, 0, 64, 64);
	images[get_arr_pos(IMG_SPIKE_BALL2)] = new ResourceLoader::ResImage(
		IMG_SPIKE_BALL2, spikeBallSurf,
		64, 0, 64, 60);
	images[get_arr_pos(IMG_SPIKE_BALL3)] = new ResourceLoader::ResImage(
		IMG_SPIKE_BALL3, spikeBallSurf,
		0, 64, 64, 64);
	images[get_arr_pos(IMG_SPIKE_BALL4)] = new ResourceLoader::ResImage(
		IMG_SPIKE_BALL4, spikeBallSurf,
		64, 64, 64, 64);
	images[get_arr_pos(IMG_CAVE_BG)] = new ResourceLoader::ResImage(
		IMG_CAVE_BG, caveStorySurf,
		0, 0, 920, 575);
	images[get_arr_pos(IMG_GIBLET1)] = new ResourceLoader::ResImage(
		IMG_GIBLET1, gibletSurf,
		0, 0, 32, 32);
	images[get_arr_pos(IMG_STONE_EMBLEM1)] = new ResourceLoader::ResImage(
		IMG_STONE_EMBLEM1, stoneEmblemSurf,
		0, 0, 64, 64);
	images[get_arr_pos(IMG_STONE_EMBLEM2)] = new ResourceLoader::ResImage(
		IMG_STONE_EMBLEM2, stoneEmblemSurf,
		64, 0, 64, 64);
	images[get_arr_pos(IMG_STONE_EMBLEM3)] = new ResourceLoader::ResImage(
		IMG_STONE_EMBLEM3, stoneEmblemSurf,
		0, 64, 64, 64);
	images[get_arr_pos(IMG_STONE_EMBLEM4)] = new ResourceLoader::ResImage(
		IMG_STONE_EMBLEM4, stoneEmblemSurf,
		64, 64, 64, 64);
	images[get_arr_pos(IMG_WALL_GUN)] = new ResourceLoader::ResImage(
		IMG_WALL_GUN, wallGunSurf,
		0, 0, 32, 32);
	images[get_arr_pos(IMG_PLR_INDCTR_1)] = new ResourceLoader::ResImage(
		IMG_PLR_INDCTR_1, plrIndctrSurf,
		0, 0, 32, 16);
	images[get_arr_pos(IMG_PLR_INDCTR_2)] = new ResourceLoader::ResImage(
		IMG_PLR_INDCTR_2, plrIndctrSurf,
		0, 16, 32, 16);
	images[get_arr_pos(IMG_PLR_INDCTR_3)] = new ResourceLoader::ResImage(
		IMG_PLR_INDCTR_3, plrIndctrSurf,
		0, 32, 32, 16);
	images[get_arr_pos(IMG_PLR_INDCTR_4)] = new ResourceLoader::ResImage(
		IMG_PLR_INDCTR_4, plrIndctrSurf,
		0, 16*3, 32, 16);
	images[get_arr_pos(IMG_BLUE_LAZER_1)] = new ResourceLoader::ResImage(
		IMG_BLUE_LAZER_1, blueLazerSurf,
		0, 16*0, 32, 16);
	images[get_arr_pos(IMG_BLUE_LAZER_2)] = new ResourceLoader::ResImage(
		IMG_BLUE_LAZER_2, blueLazerSurf,
		0, 16*1, 32, 16);
	images[get_arr_pos(IMG_BLUE_LAZER_3)] = new ResourceLoader::ResImage(
		IMG_BLUE_LAZER_3, blueLazerSurf,
		0, 16*2, 32, 16);
	images[get_arr_pos(IMG_RED_LAZER_1)] = new ResourceLoader::ResImage(
		IMG_RED_LAZER_1, blueLazerSurf,
		32, 16*0, 32, 16);
	images[get_arr_pos(IMG_RED_LAZER_2)] = new ResourceLoader::ResImage(
		IMG_RED_LAZER_2, blueLazerSurf,
		32, 16*1, 32, 16);
	images[get_arr_pos(IMG_RED_LAZER_3)] = new ResourceLoader::ResImage(
		IMG_RED_LAZER_3, blueLazerSurf,
		32, 16*2, 32, 16);
	
	images[get_arr_pos(IMG_COOL_GUY_WALK_RIGHT_1)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_WALK_RIGHT_1, coolGuySurf,
		61, 173, 32, 73);
	images[get_arr_pos(IMG_COOL_GUY_WALK_RIGHT_2)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_WALK_RIGHT_2, coolGuySurf,
		138, 173, 35, 75);
	images[get_arr_pos(IMG_COOL_GUY_WALK_LEFT_1)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_WALK_LEFT_1, coolGuySurf,
		143, 256, 31, 72);
	images[get_arr_pos(IMG_COOL_GUY_WALK_LEFT_2)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_WALK_LEFT_2, coolGuySurf,
		61, 255, 35, 74);
	images[get_arr_pos(IMG_COOL_GUY_STAND_RIGHT)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_STAND_RIGHT, coolGuySurf,
		26, 173, 27, 73);
	images[get_arr_pos(IMG_COOL_GUY_STAND_LEFT)] = new ResourceLoader::ResImage(
		IMG_COOL_GUY_STAND_LEFT, coolGuySurf,
		18, 255, 37, 75);
		
	images[get_arr_pos(IMG_FINISH_LEVEL_1)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_1, finishLevelSurf,
		0, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_2)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_2, finishLevelSurf,
		128*1, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_3)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_3, finishLevelSurf,
		128*2, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_4)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_4, finishLevelSurf,
		128*3, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_5)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_5, finishLevelSurf,
		128*4, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_6)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_6, finishLevelSurf,
		128*5, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_7)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_7, finishLevelSurf,
		128*6, 0, 128, 128);
	images[get_arr_pos(IMG_FINISH_LEVEL_8)] = new ResourceLoader::ResImage(
		IMG_FINISH_LEVEL_8, finishLevelSurf,
		128*7, 0, 128, 128);
		
	return 1.0f;
}

void ResourceLoader::draw_image(int img_type, SDL_Surface *screen, float x, float y)
{
	draw_image(img_type, screen, x, y, NULL, 0);
}
void ResourceLoader::draw_image(int img_type, SDL_Surface *screen, float x, float y, ImageEffect **effects, int effects_size)
{
	ResourceLoader::ResImage *resImg = get_image(img_type);
	dst_rect->x = x;
	dst_rect->y = y;
	dst_rect->w = resImg->getSrcRect()->w;
	dst_rect->h = resImg->getSrcRect()->h;
	SDL_Rect src_rect;
	src_rect.x = resImg->getSrcRect()->x;
	src_rect.y = resImg->getSrcRect()->y;
	src_rect.w = resImg->getSrcRect()->w;
	src_rect.h = resImg->getSrcRect()->h;
	if (effects != NULL && effects_size != 0)
		for (int i = 0; i < effects_size; ++i)
			effects[i]->apply(dst_rect, &src_rect);
	/*
	SDL_BlitSurface( resLoader->get_image(IMG_TEST), src_rect, screen, dst_rect );*/
	SDL_BlitSurface(
		resImg->getImgFile(), 
		&src_rect, 
		screen, 
		dst_rect);
}