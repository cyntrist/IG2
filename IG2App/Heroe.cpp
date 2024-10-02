#include "Heroe.h"

void Heroe::init()
{



}

void Heroe::setScale(Vector3 s)
{
	this->mNode->setScale(s);
}

void Heroe::setRotation(Vector3 r)
{
	mNode->yaw(Ogre::Degree(r.z));
	mNode->roll(Ogre::Degree(r.x));
	mNode->pitch(Ogre::Degree(r.y));
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
