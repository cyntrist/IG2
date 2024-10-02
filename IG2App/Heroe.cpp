#include "Heroe.h"

void Heroe::init()
{



}

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP) {
		std::cout << "UP " << std::endl;
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		std::cout << "RIGHT " << std::endl;

	}	
	else if (evt.keysym.sym == SDLK_DOWN) {
		std::cout << "DOWN " << std::endl;

	}	
	else if (evt.keysym.sym == SDLK_LEFT) {
		std::cout << "LEFT " << std::endl;

	}


	return true;
}

void Heroe::addPoint(int i)
{
	puntos += i;
}
