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

		newdir = { 0, 1, 0 };
	}
	else if (evt.keysym.sym == SDLK_RIGHT) {
		std::cout << "RIGHT " << std::endl;
		setOrientation({ -1, 0, 0 });


		newdir = { 1, 0, 0 };

	}	
	else if (evt.keysym.sym == SDLK_DOWN) {
		std::cout << "DOWN " << std::endl;

		setOrientation({ 0, 1,0 });


		newdir = { 0, -1, 0 };

	}	
	else if (evt.keysym.sym == SDLK_LEFT) {
		std::cout << "LEFT " << std::endl;
		setOrientation({ 1, 0, 0 });

		newdir = { -1, 0, 0 };

	}


	return true;
}

void Heroe::updateMovement(Vector3 vec)
{
	if (checkMiddle() && newdir != dir) {	

		
		//std::cout << "passable block? " << checkCollision(newdir) << std::endl;

		// si no se choca
		if (checkCollision(newdir)) {

			std::cout << "CAMBIA DIRECCION真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真" << std::endl;

			dir = newdir;
		}

	}


	//std::cout << "IS COLLISIONING? " << checkCollision(dir) << std::endl;
	if (checkCollision(dir))
	{
		std::cout << "SE MUEVE真真 真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真" << std::endl;

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
	return checkCollision(vec);
}

bool Heroe::checkCollision(Vector3 dir)
{
	int id = ((trunc(getPosition().x/WALL_LENGTH)) + (trunc(getPosition().y/ WALL_LENGTH)))/5 ;
	id += 180;
	std::cout << "dir " << dir << std::endl;

	if (dir.x == 1) id++;
	else if (dir.x == -1) id--;
	else if (dir.y == 1) id += 19;
	else if (dir.y == -1) id -= 19;
	std::cout << "el id de el player es " << id << std::endl;

	if (lab->getLabyrinth()[id] == nullptr) return true;

	//std::cout << "el tipo del bloque es: " << (int)lab->getLabyrinth()[id]->Type() << std::endl;
	std::cout << "el tipo del bloque es: " << (int)lab->getBlock(id)->Type() << std::endl;

	if (lab->getLabyrinth()[id]->Type() == Block::TYPE::WALL)
		return true;
	else if (lab->getLabyrinth()[id]->Type() == Block::TYPE::PEARL)
		return false;
	else
		return true;


/*
//int i;	// indice del bloque con el que se pega

	//Vector3 posHero = (getPosition()) / WALL_LENGTH; // Posicion en el laberinto normalizado.
	//int id;

	//

	//i = trunc(getPosition().x) * WALL_LENGTH + trunc(getPosition().y);
	//Vector3 orientation = getOrientation();

	//std::cout << "this block index is: " << i << std::endl;

	//auto* a = lab->getLabyrinth()[i];




	//if (a == nullptr) {
	//	return true;
	//}

	//std::cout << "this block is: " << (int)a->Type() << std::endl;


	//std::cout << "this block type is: " << (int)a->Type() << std::endl;
	//std::cout << "direction is: " << dir << std::endl;


	//if (a->Type() == Block::TYPE::WALL) return false;
	//else if (a->Type() == Block::TYPE::PEARL) return true;
	//else return true;

*/
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
