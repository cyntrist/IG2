#include "Villain.h"

#include "Heroe.h"
#include "Labyrinth.h"

void Villain::frameRendered(const FrameEvent& evt)
{
	for (auto d : availableDirs) d = true;
	if (checkMiddle())
	{
		if (checkCollisions(dir))
		{
			//if (checkCollisions({1, 0, 0}))
			//	newDir = {0, -1, 0};
			//else if (checkCollisions({-1, 0, 0}))
			//	newDir = {-1, 0, 0};
			//else if (checkCollisions({0, 1, 0}))
			//	newDir = {0, 1, 0};
			//else if (checkCollisions({0, -1, 0}))
			//	newDir = {0, -1, 0};
			//dir = newDir;
			//setOrientation(-dir);


			/// 
			//if (checkCollisions({-1, 0, 0}))
			//	availableDirs[0] = false;
			//if (checkCollisions({0, 1, 0}))
			//	availableDirs[1] = false;
			//if (checkCollisions({1, 0, 0}))
			//	availableDirs[2] = false;
			//if (checkCollisions({0, -1, 0}))
			//	availableDirs[3] = false;
		}
	}


	if (dir == Vector3().ZERO)
	{
		//if (checkCollisions({1, 0, 0}))
		//	newDir = {0, -1, 0};
		//else if (checkCollisions({-1, 0, 0}))
		//	newDir = {-1, 0, 0};
		//else if (checkCollisions({0, 1, 0}))
		//	newDir = {0, 1, 0};
		//else if (checkCollisions({0, -1, 0}))
		//	newDir = {0, -1, 0};

		//dir = newDir;

		if (checkCollisions({-1, 0, 0}))
			availableDirs[0] = false;
		if (checkCollisions({0, 1, 0}))
			availableDirs[1] = false;
		if (checkCollisions({1, 0, 0}))
			availableDirs[2] = false;
		if (checkCollisions({0, -1, 0}))
			availableDirs[3] = false;
	}


	newDir = {0, 0, 0};
	for (int i = 0; i < availableDirs.size(); i++)
	{
		if (availableDirs[i])
		{
			switch (i)
			{
			case 0: newDir = {-1, 0, 0};
				break;
			case 1: newDir = {0, 1, 0};
				break;
			case 2: newDir = {1, 0, 0};
				break;
			case 3: newDir = {0, -1, 0};
				break;
			default: break;
			}
			dir = newDir;
			setOrientation(-dir);
			move(dir);
		}
	}

	dir = newDir;
	setOrientation(-dir);
	move(dir);
	updateEstela();
}

bool Villain::checkCollisions(Vector3 dir)
{
	bool colisiona = false;
	Block* aux = getBlock(dir);

	if (aux == nullptr || aux->Type() == Block::WALL)
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
	//return lab->getBlock(getPosition(), dir);

	Block* block;
	auto laby = lab->getLabyrinth();

	int offsetx = lab->getLabSize().x / lab->getWallSize().x / 2;
	int offsety = lab->getLabSize().y / lab->getWallSize().y / 2;

	int auxx = getPosition().x / WALL_LENGTH;
	int auxy = getPosition().y / WALL_LENGTH;

	int x = offsetx + trunc(auxx / 5);
	int y = offsety + trunc(auxy / 5);

	y += dir.y;
	x += dir.x;

	//std::cout << "JODER: " << x << " " << y << std::endl;

	if (x < 0 || y < 0 || x >= 19 || y >= 19) return nullptr;
	block = lab->getLabyrinth()[y][x];

	if (block == nullptr) return nullptr;

	//string auxt = "NONE";
	//auxt = block->Type();
	//if (block->Type() == Block::TYPE::WALL) auxt = "WALL";
	//if (block->Type() == Block::TYPE::PEARL) auxt = "PEARL";
	//std::cout << "TYPE " << auxt << std::endl << std::endl << std::endl;

	return block;
}

void Villain::updateEstela()
{
	if (estela != nullptr)
	{
		estela->setPosition(mNode->getPosition());
	}
}
