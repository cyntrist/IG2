#include "Heroe.h"

void Heroe::keypressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP) {
		
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {

	}	
	else if (evt.keysym.sym == SDLK_DOWN) {

	}	
	else if (evt.keysym.sym == SDLK_LEFT) {

	}

}

void Heroe::addPoint(int i)
{
	puntos += i;
}
