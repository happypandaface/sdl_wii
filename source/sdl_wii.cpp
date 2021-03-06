// normal includes
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#ifdef WINDOWS_BUILD
	#include <windows.h>
#endif
//#include <gccore.h>
//#include <wiiuse/wpad.h> 

// SDL includes
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// my cross-platform stuff
#include "controller.h"
#include "res_loader.h"
#include "audio.h"
#include "level_select.h"

// this should hold everything
#include "game_properties.h"
#include "object_holder.h"
#include "gravity.h"
#include "camera.h"
#include "animation_holder.h"

#include "player.h"
#include "spike_ball.h"
#include "wall.h"
#include "giblet.h"
#include "background.h"
#include "stone_emblem.h"
#include "wall_gun.h"
#include "blue_lazer.h"
#include "finish_level.h"
#include "imgfx_split.h"
 
// screen surface, the place where everything will get print onto
SDL_Surface *screen = NULL;
 
void init(GameProperties *gameProps)
{
 
	// initialize SDL video. If there was an error SDL shows it on the screen
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
		SDL_Delay( 5000 );
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG_BUILD
		freopen( "CON", "w", stdout );
		freopen( "CON", "w", stderr );
	#endif
 
	// button initialization
	//WPAD_Init();
 
	// make sure SDL cleans up before exit
	atexit(SDL_Quit);
	//SDL_ShowCursor(SDL_DISABLE);
 
	// create a new window
	//screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);
	screen = SDL_SetVideoMode(gameProps->getRes()->getX(), gameProps->getRes()->getY(), 16, SDL_DOUBLEBUF);
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

void startLevel(GameProperties *gameProps, ObjectHolder *objHolder)
{
	// now that we're done adding all the walls, we gotta calculate all the wall's neighbors
	//  to mitigate the foul glitch only known as... "the you sometimes get tripped up when
	//  going over floors glitch" also it makes the tiles look nicer
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		Wall *wll = dynamic_cast<Wall*>(curr);
		if (wll)
		{
			wll->calcNeighbors(objHolder, gameProps);
		}
	}
	objHolder->destroyIterator(objIter);
}
 
int main(int argc, char** argv)
{
	srand(time(NULL));
	// main function. Always starts first
 
	// to stop the while loop
	bool done = false;
	
	GameProperties *gameProps = new GameProperties();
	gameProps->setTileSize(64, 64);
 
	// start init() function
	init(gameProps);
	
	Uint32 old_time = 0;
	Uint32 current_time = 0;
	float ftime = 0;
	
	Controller *contrlr = new Controller();
	AudioPlayer *audioPlayer = new AudioPlayer();
	audioPlayer->init();
	ObjectHolder *objHolder = new ObjectHolder();
	ObjectIterator *objIter = objHolder->getIterator();
	
	// these must be called in this order:
	gameProps->getResLoader()->load();
	gameProps->getAnimHolder()->load(gameProps->getResLoader());
	gameProps->getLevelSelect()->load(gameProps);
	
	//ImgFxSplit *imgfxsplit = new ImgFxSplit(40, 40, 300, 300);
	//gameProps->getResLoader()->useEffect(imgfxsplit);
	
	Gravity *grav = new Gravity();
	grav->setStrength(20);
	
	delete objHolder;
	objHolder = new ObjectHolder();
	
	//makeLevel1(gameProps, objHolder);
	
	//startLevel(gameProps, objHolder);
 
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
		
		if (gameProps->isEndingLevel())
		{
			gameProps->getLevelSelect()->update(contrlr, gameProps, ftime);
			gameProps->getLevelSelect()->draw(gameProps, screen, ftime);
			if (gameProps->getLevelSelect()->getSelection() != 0)
			{
				objHolder->destroyObjs();
				
				gameProps->setPlayers(0);
				gameProps->getCam()->clear();
				gameProps->makeLevel(objHolder);
				gameProps->unfreeze();
				startLevel(gameProps, objHolder);
				
				gameProps->unEndLevel();
				gameProps->addObjsTo(NULL);
			}
		}else
		{
			if (gameProps->getPlayersLeft() == 0)
			{
				Pos2 *spawnPos = gameProps->getSpawnPos();
				if (spawnPos)
				{
					Player *p1 = new Player();
					p1->setController(0);
					p1->setPos(spawnPos->getX(), spawnPos->getY());
					p1->load(gameProps->getResLoader(), gameProps->getAnimHolder());
					objHolder->addObject(p1);
					
					Player *p2 = new Player();
					p2->setController(1);
					p2->setPos(spawnPos->getX(), spawnPos->getY());
					p2->load(gameProps->getResLoader(), gameProps->getAnimHolder());
					objHolder->addObject(p2);
					
					gameProps->addPlayer();
					gameProps->addPlayer();
					
					gameProps->getCam()->addFollow(p1);
					gameProps->getCam()->addFollow(p2);
				}
			}
			
			grav->update(objHolder, ftime);
			
			objHolder->resetIterator(objIter);
			BaseObject *curr;
			while(objHolder->hasNext(objIter))
			{
				curr = objHolder->next(objIter);
				if (!gameProps->isFrozen() || curr->checkType(TYP_UNFRZN))
					curr->update(objHolder, gameProps, audioPlayer, contrlr, ftime);
				curr->draw(gameProps->getResLoader(), gameProps, screen);
			}
			
			objHolder->resetIterator(objIter);// restart to remove objs
			curr = objHolder->next(objIter); // this has to be before the while loop /
				// for the while loop to work and remove correctly
			while(curr != NULL)
			{
				BaseObject *objToRemove = NULL;
				if (curr->checkType(TYP_DEAD))
				{
					curr->doDeath(objHolder, gameProps, audioPlayer, contrlr, ftime);
					objToRemove = curr;
				}
				if (objHolder->hasNext(objIter))
					curr = objHolder->next(objIter);
				else
					curr = NULL;
				if (objToRemove != NULL)
					objHolder->removeObject(objToRemove, 1);
				if (curr == NULL)
					break;
			}
			gameProps->addObjsTo(objHolder);
			
			gameProps->getCam()->update(gameProps, ftime);
		}
		
		SDL_Flip(screen);
	}
	
	// start cleanup
	objHolder->destroyIterator(objIter);
	delete objHolder;
	delete contrlr;
	delete gameProps;
	delete audioPlayer;
	SDL_Quit();
	exit(EXIT_SUCCESS);
 
	return 0;
}