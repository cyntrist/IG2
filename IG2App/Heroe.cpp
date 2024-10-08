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
	mNode->roll(Ogre::Degree(r.x));
	mNode->pitch(Ogre::Degree(r.y));
	mNode->yaw(Ogre::Degree(r.z));
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	updateMovement(dir);


}

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP) {
		std::cout << "UP " << std::endl;
		//updateRotation();

		newdir = dir = { 0, 1, 0 };
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

void Heroe::updateMovement(Vector3 vec)
{
	if (canMove(vec)) {
		mNode->translate(dir);

	}
}

void Heroe::updateRotation(int degree)
{
	// cambia la rotacion

	// actualiza la direccion actual
}

bool Heroe::canMove(Vector3 vec)
{
	return true;
}

bool Heroe::checkCollision()
{
	// mirar vector direccion del hero, multiplicar por el tamaño del bloque y pedirle al laberinto que te
	// de el objeto de esa posicion, si es una pared no se mueve, si no pues jijij

	return false;
}

void Heroe::addPoint(int i)
{
	puntos += i;
}
