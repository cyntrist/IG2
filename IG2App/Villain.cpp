#include "Villain.h"

#include "Heroe.h"
#include "Labyrinth.h"

void Villain::frameRendered(const FrameEvent& evt)
{
	if (checkMiddle())
	{
		// si choca, busca una nueva direccion valida
		if (checkCollisions(dir))
		{
			if (newDir != dir)
			{
				if (checkCollisions({1, 0, 0}))
					newDir = {0, -1, 0};
				else if (checkCollisions({-1, 0, 0}))
					newDir = {-1, 0, 0};
				else if (checkCollisions({0, 1, 0}))
					newDir = {0, 1, 0};
				else if (checkCollisions({0, -1, 0}))
					newDir = {0, -1, 0};
			}
			dir = newDir;
			setOrientation(-dir);
		}
	}

	move(dir);

	if (dir == Vector3().ZERO)
	{
		if (checkCollisions({1, 0, 0}))
			newDir = {1, 0, 0};
		else if (checkCollisions({-1, 0, 0}))
			newDir = {-1, 0, 0};
		else if (checkCollisions({0, 1, 0}))
			newDir = {0, 1, 0};
		else if (checkCollisions({0, -1, 0}))
			newDir = {0, -1, 0};

		dir = newDir;
	}
}

bool Villain::checkCollisions(Vector3 dir)
{
	bool colisiona = false;
	Block* aux = getBlock(dir);

	if (aux == nullptr || !aux->isPass())
		colisiona = true;

	return colisiona;
}

bool Villain::checkMiddle() const
{
	bool mid = false;
	int x = mNode->getPosition().x;
	int y = mNode->getPosition().y;
	int z = mNode->getPosition().z;

	Vector3 centro(x % 100, y % 100, z % 100);
	Vector3 aux = {2, 2, 5};

	if (centro.x <= aux.x && centro.y <= aux.y) mid = true;

	return mid;
}

Block* Villain::getBlock(Vector3 dir)
{
	int offsetx = lab->getLabSize().x / lab->getWallSize().x / 2;
	int offsety = lab->getLabSize().y / lab->getWallSize().y / 2;

	int auxx = getPosition().x / WALL_LENGTH;
	int auxy = getPosition().y / WALL_LENGTH;

	int x = offsetx + trunc(auxx / 5);
	int y = offsety + trunc(auxy / 5);

	y += dir.y;
	x += dir.x;

	if (x < 0 || y < 0) return nullptr;

	/*string auxt = "NONE";
	auxt = lab->getLabyrinth()[x][y]->Type();
	if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::WALL) auxt = "WALL";
	if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::PEARL) auxt = "PEARL";
	if (lab->getLabyrinth()[x][y]->Type() == Block::TYPE::NONE) auxt = "NONE";
	std::cout << " TYPE " << auxt << std::endl << std::endl << std::endl;*/

	return lab->getLabyrinth()[y][x];
}
