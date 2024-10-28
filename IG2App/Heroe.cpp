#include "Heroe.h"
#include "Block.h"

void Heroe::init()
{



}

void Heroe::setScale(Vector3 s)
{
	this->mNode->setScale(s);
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
	std::cout << "colisiona?? " << checkCollision(dir) << std::endl;


	if (checkMiddle() && newdir != dir) {	

		// si no se choca
		if (!checkCollision(newdir)) {
			//std::cout << "CAMBIA DIRECCION真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真" << std::endl;
			dir = newdir;
		}
	}

	if (checkCollision(dir) && checkMiddle())
	{
		dir = { 0,0,0 };
		//std::cout << "SE MUEVE真真 真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真真" << std::endl;
	}

	mNode->translate(dir);
	

}

bool Heroe::canMove(Vector3 vec)
{
	return checkCollision(vec);
}

bool Heroe::checkCollision(Vector3 dir)
{
	bool colisiona = false;
	int offsetx = lab->getLabSize().x / lab->getWallSize().x/2;
	int offsety = lab->getLabSize().y / lab->getWallSize().y/2;


	int x = offsetx + 1 + ((trunc((getPosition().x) / WALL_LENGTH))) / 5;
	int y = offsety + 1 + ((trunc((getPosition().y) / WALL_LENGTH))) / 5;

	y = lab->getLabSize().x / lab->getWallSize().x - y;
	std::cout << "x " << x << "y " << y << std::endl;

	y += dir.y;
	x += dir.x;


	if (lab->getLabyrinth()[x][y] == nullptr) colisiona = true;
	else if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::WALL)
		colisiona = true;
	else if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::PEARL)
		colisiona =  false;	
	else if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::NONE)
		colisiona =  false;

	return colisiona;
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
