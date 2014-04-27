// normal includes
#include <stdlib.h>
#include <iostream>
#include <time.h>
//#include <gccore.h>
//#include <wiiuse/wpad.h> 

// SDL includes
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// my cross-platform stuff
#include "controller.h"
#include "res_loader.h"
#include "audio.h"

// this should hold everything
#include "game_properties.h"
#include "object_holder.h"
#include "gravity.h"

#include "player.h"
#include "wall.h"
 
// screen surface, the place where everything will get print onto
SDL_Surface *screen = NULL;
 
void init()
{
 
	// initialize SDL video. If there was an error SDL shows it on the screen
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
		SDL_Delay( 5000 );
		exit(EXIT_FAILURE);
	}
 
	// button initialization
	//WPAD_Init();
 
	// make sure SDL cleans up before exit
	atexit(SDL_Quit);
	//SDL_ShowCursor(SDL_DISABLE);
 
	// create a new window
	screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);
	if ( !screen )
	{
		fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
		SDL_Delay( 5000 );
		exit(EXIT_FAILURE);
	}
}
 
// this will be used in further lessons, not in lesson 1
void apply_surface ( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
 
	 // make a temporary rectangle to hold the offsets
	 SDL_Rect offset;
 
	 // give the offsets to the rectangle
	 offset.x = x;
	 offset.y = y;
 
	 // blit the surface
	 SDL_BlitSurface( source, NULL, destination, &offset );
}
 
int main(int argc, char** argv){
	// main function. Always starts first
 
	// to stop the while loop
	bool done = false;
 
	// start init() function
	init();
	
	Uint32 old_time = 0;
	Uint32 current_time = 0;
	float ftime = 0;
	
	Controller *contrlr = new Controller();
	ResourceLoader *resLoader = new ResourceLoader();
	GameProperties *gameProps = new GameProperties();
	gameProps->setTileSize(64, 64);
	AudioPlayer *audioPlayer = new AudioPlayer();
	audioPlayer->init();
	ObjectHolder *objHolder = new ObjectHolder();
	ObjectIterator *objIter = objHolder->getIterator();
	
	resLoader->load();
	
	Gravity *grav = new Gravity();
	grav->setStrength(20);
	
	Animation *a1 = new Animation(2);
	a1->addFrame(IMG_TEST, 0, 0);
	a1->addFrame(IMG_DIRT_SQUARE, 0, 0);
	a1->setBaseSpeed(.2);
	Animation *a2 = new Animation(2);
	a2->addFrame(IMG_DIRT_SQUARE, 0, 0);
	a2->addFrame(IMG_TEST, 0, 0);
	a2->setBaseSpeed(.2);
	
	Player *p1 = new Player();
	p1->setController(0);
	p1->load(resLoader);
	p1->setAnimation(a1);
	objHolder->addObject(p1);
	
	Player *p2 = new Player();
	p2->setController(1);
	p2->load(resLoader);
	p2->setAnimation(a1);
	objHolder->addObject(p2);
	
	for (int i = 0; i < 100; ++i)
	{
		Wall *w = new Wall();
		w->load(resLoader);
		w->setPos(i, 6);
		w->setAnimation(a2);
		objHolder->addObject(w);
	}
 
	// this is the endless while loop until done = true
	while (!done)
	{
		contrlr->update();
		if (contrlr->key_down(0, CTRL_QUIT))
			done = 1;
		
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 0, 0));
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime = (current_time - old_time) / 1000.0f;
		if (ftime > .1)
			ftime = .1;
		
		grav->update(objHolder, ftime);
		
		objHolder->resetIterator(objIter);
		BaseObject *curr;
		while(objHolder->hasNext(objIter))
		{
			curr = objHolder->next(objIter);
			curr->update(objHolder, gameProps, audioPlayer, contrlr, ftime);
			curr->draw(resLoader, gameProps, screen);
		}
		/*
		p1->update(gameProps, audioPlayer, contrlr, ftime);
		p1->draw(gameProps, screen);
		
		p2->update(gameProps, audioPlayer, contrlr, ftime);
		p2->draw(gameProps, screen);
		
		w->update(gameProps, audioPlayer, contrlr, ftime);
		w->draw(gameProps, screen);
		*/
		
		SDL_Flip(screen);
	}
	
	// start cleanup
	objHolder->destroyIterator(objIter);
	delete objHolder;
	delete contrlr;
	delete resLoader;
	delete gameProps;
	delete audioPlayer;
	SDL_Quit();
	exit(EXIT_SUCCESS);
 
	return 0;
}