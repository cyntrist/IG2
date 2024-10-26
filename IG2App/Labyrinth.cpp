#include "Labyrinth.h"

#include "fstream"
#include "Wall.h"
#include "Pearl.h"
#include "Heroe.h"

#include <iostream>
#include <iomanip>
#include <fstream>

Labyrinth::Labyrinth(SceneNode* sn, SceneManager* sm, const string& path) : node(nullptr)
{
	// opening stream
	ifstream file(path);
	if (!file.is_open())
	{
		cout << "Error en la lectura del archivo." << endl;
		return;
	}

	// init params
	int nf = 0, nc = 0; // number rows number cols
	file >> nf >> nc;

	// reading file
	std::vector<string> grid;
	string row;
	for (int i = 0; i < nf; i++)
	{
		file >> row;
		grid.push_back(row);
	}

	// parsing data into objects
	for (int i = 0; i < nf; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (grid[j][i] == 'x')
			{
				Block* w = new Wall(
					{0, 0, 0},
					sn,
					sm,
					WALL_NAME + to_string(i * nc + j)
				);

				wallSize = w->calculateBoxSize();
				w->setPosition({
					wallSize.x * i,
					wallSize.y * j,
					LAB_DEPTH
				});
				w->setType(Block::TYPE::WALL);
				w->setPass(false);

				blocks.push_back(w);
			}
			else if (grid[j][i] == 'o')
			{
				auto p = new Pearl(
					{0, 0, 0},
					sn,
					sm,
					PEARL_NAME + to_string(i * nc + j)
				);

				p->setPosition({
					wallSize.x * i,
					wallSize.y * j,
					LAB_DEPTH
				});
				p->setScale({PEARL_SIZE, PEARL_SIZE, PEARL_SIZE});
				p->setType(Block::TYPE::PEARL);
				p->setPass(true);
				blocks.push_back(p);

			}
			else if (grid[j][i] == 'h')
			{
				Vector3 vecH = { 0, 0, H_DEPTH };

				Heroe* h = new Heroe(
					vecH,
					sm->getRootSceneNode()->createChildSceneNode("nHeroe"),
					sm,
					"Sinbad.mesh",
					this);
				h->setScale({ 10, 10, 10 });
				h->setRotation({ 0,90,0 });
				hero.push_back(h);
			}
			else {

				Block* b = nullptr;
				blocks.push_back(b);

			}
		}
	}

	labSize = { wallSize.x * nf, wallSize.y * nc };

	// recoloca el laberinto
	for (auto b : blocks)
		b->setPosition(
			b->getPosition().x - labSize.x/2 + wallSize.x/2,
			b->getPosition().y - labSize.y/2 + wallSize.y/2,
			b->getPosition().z
		);
	
	file.close();
}

Labyrinth::~Labyrinth()
{
	//for (const auto i : walls)
	//	delete i;
	//for (const auto i : pearls)
	//	delete i;
	walls.clear();
	pearls.clear();
}

Block* Labyrinth::getBlock(Vector3 pos)
{
	// ¿?¿?¿?¿


	return nullptr;
}
