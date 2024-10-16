#include "Heroe.h"
#include "Block.h"

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
	if (checkMiddle() && !checkCollision()) {

	}
	mNode->translate(dir);

}

void Heroe::updateRotation(int degree)
{
	// cambia la rotacion
	mNode->yaw(Ogre::Degree(degree));

	// actualiza la direccion actual
}

bool Heroe::canMove(Vector3 vec)
{
	return checkCollision();
}

Block* Heroe::checkCollision()
{
	int i;	// indice del bloque con el que se pega

	i = trunc(getPosition().x) * lab->getLabSize().x + trunc(getPosition().y);
	Vector3 orientation = getOrientation();

	// devuelve el propio bloque
	return lab->getLabyrinth()[i];
}

bool Heroe::checkMiddle()
{
	int x, y, z;
	x = mNode->getPosition().x;
	y = mNode->getPosition().y;
	z = mNode->getPosition().z;

	Vector3 centro(x % 100, y % 100, z % 100);

	//Si todos los numeros son multiplos de 100 esta en un centro
	return centro == Vector3().ZERO;
}

void Heroe::addPoint(int i)
{
	puntos += i;
}
