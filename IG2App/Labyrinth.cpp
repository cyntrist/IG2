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
				auto w = new Wall(
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
				walls.push_back(w);
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
				pearls.push_back(p);
			}
			else if (grid[j][i] == 'h')
			{
				Vector3 vecH = { 0, 0, H_DEPTH };
				Heroe* h = new Heroe(
					vecH,
					sm->getRootSceneNode()->createChildSceneNode("nHeroe"),
					sm,
					"Sinbad.mesh");
				h->setScale({ 10, 10, 10 });
				h->setRotation({ 0,90,0 });
				hero.push_back(h);
			}
		}
	}

	labSize = { wallSize.x * nf, wallSize.y * nc };

	for (auto w : walls)
		w->setPosition(
			w->getPosition().x - labSize.x/2 + wallSize.x/2,
			w->getPosition().y - labSize.y/2 + wallSize.y/2,
			w->getPosition().z
		);

	
	for (auto p : pearls)
		p->setPosition(
			p->getPosition().x - labSize.x/2 + wallSize.x/2,
			p->getPosition().y - labSize.y/2 + wallSize.y/2,
			p->getPosition().z
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
