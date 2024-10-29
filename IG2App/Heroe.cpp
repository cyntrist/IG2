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
	if (checkMiddle() && newdir != dir) {

		if(!checkCollision(newdir))
			dir = newdir;
	}

	if (checkCollision(dir) && checkMiddle()) {
		dir = { 0,0,0 };
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

	int auxx = (getPosition().x) / WALL_LENGTH;
	int auxy = (getPosition().y) / WALL_LENGTH;

	int x = offsetx + trunc(auxx / 5);
	int y = offsety + trunc(auxy / 5);
	//std::cout << "dir x " << dir.x << "dir y " << dir.y << std::endl;


	y += dir.y;
	x += dir.x;

	//std::cout << "x " << x << "y " << y << std::endl;

	//string auxt = "NONE";
	//auxt = lab->getLabyrinth()[x][y]->Type();
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::WALL) auxt = "WALL";
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::PEARL) auxt = "PEARL";
	//if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::NONE) auxt = "NONE";
	//std::cout << " TYPE " << auxt << std::endl << std::endl << std::endl;


	if (lab->getLabyrinth()[x][y] == nullptr) colisiona = true;
	if (lab->getLabyrinth()[x][y]->isPass()) colisiona = false;
	if (!lab->getLabyrinth()[x][y]->isPass()) colisiona = true;

	return colisiona;
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
