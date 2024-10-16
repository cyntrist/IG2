#include "Heroe.h"
#include "Labyrinth.h"


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

void Heroe::setOrientation(Vector3 vec)
{
	mNode->setDirection(vec.x, vec.y, vec.z, Node::TS_WORLD);
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	updateMovement(dir);

}

bool Heroe::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP) {
		std::cout << "UP " << std::endl;
		setOrientation({0, -1, 0});

		newdir = dir = { 0, 1, 0 };
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		std::cout << "RIGHT " << std::endl;
		setOrientation({ -1, 0, 0 });
		newdir = dir = { 1, 0, 0 };
	}	
	else if (evt.keysym.sym == SDLK_DOWN) {
		std::cout << "DOWN " << std::endl;
		setOrientation({ 0, 1,0 });
		newdir = dir = { 0, -1, 0 };
	}	
	else if (evt.keysym.sym == SDLK_LEFT) {
		std::cout << "LEFT " << std::endl;
		setOrientation({ 1, 0, 0 });
		newdir = dir = { -1, 0, 0 };
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
	mNode->yaw(Ogre::Degree(degree));

	// actualiza la direccion actual
}

bool Heroe::canMove(Vector3 vec)
{
	bool move = false;
	// mira si esta en el medio del bloque
	// ejes x/y
	int x = mNode->getPosition().x;
	int y = mNode->getPosition().y;


	//std::cout << "pos x: " << x << ", pos y: " << y << std::endl;
	if (x%(int)lab->getWallSize().x == 0 && y%(int)lab->getWallSize().y == 0) {
		// esta en el medio ???
		//std::cout << "MEDIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << std::endl;
		//move = false;

		int a = x / (int)lab->getWallSize().x;
		int b = y / (int)lab->getWallSize().y;

		//auto& typ = lab->getType(a,b);
	}


	return move;
}

bool Heroe::checkCollision()
{
	// mirar vector direccion del hero, multiplicar por el tamaño del bloque y pedirle al laberinto que te
	// de el objeto de esa posicion, si es una pared no se mueve, si no pues jijij
	Vector3 direc = dir * 50;

	return false;
}

void Heroe::addPoint(int i)
{
	puntos += i;
}
