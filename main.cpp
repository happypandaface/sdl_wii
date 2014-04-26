// normal includes
#include <stdlib.h>
#include <time.h>
//#include <gccore.h>
//#include <wiiuse/wpad.h> 

// SDL includes
#include <SDL/sdl.h>
#include <SDL/sdl_image.h>

// my cross-platform stuff
#include "controller.h"
#include "image_loader.h"
 
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
	SDL_ShowCursor(SDL_DISABLE);
 
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
 
void cleanup(){
 
	 // we have to quit SDL
	 SDL_Quit();
	 exit(EXIT_SUCCESS);
}
 
int main(int argc, char** argv){
	// main function. Always starts first
 
	// to stop the while loop
	bool done = false;
 
	// start init() function
	init();
	
	// because I can't get sdl_image 1.2 to work on the computer
	// I need to have wrapper functions for different function names
	// between sdl_image 1.2 and sdl_image2
	SDL_Surface *spriteImage = load_image(0);
 
	// this is the endless while loop until done = true
	while (!done)
	{
		// this will make the red background
		// the first argument says it must be placed on the screen
		// the third argument gives the color in RGB format. You can change it if you want
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 0, 0));
		SDL_BlitSurface( spriteImage, NULL, screen, NULL );
		// scans if a button was pressed
		controller_update();
		if (key_down(0, CTRL_QUIT))
			done = 1;
		
		
		SDL_Flip(screen);
	}
	
	SDL_FreeSurface( spriteImage );
	
	// start cleanup() function
	cleanup();
 
	return 0;
}