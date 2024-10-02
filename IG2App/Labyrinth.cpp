#include "Labyrinth.h"

#include "fstream"
#include "Wall.h"
#include "Pearl.h"
#include "Heroe.h"

#include <iostream>
#include <iomanip>
#include <fstream>

Labyrinth::Labyrinth(SceneNode* sn, SceneManager* sm, const string& path)
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

				sWallSize = w->calculateBoxSize();
				w->setPosition({
					LAB_XSET + sWallSize.x * i,
					LAB_YSET + sWallSize.y * j,
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
					LAB_XSET + sWallSize.x * i,
					LAB_YSET + sWallSize.y * j,
					LAB_DEPTH
				});
				p->setScale({PEARL_SIZE, PEARL_SIZE, PEARL_SIZE});
				pearls.push_back(p);
			}
			else if (grid[j][i] == 'h')
			{
				auto h = new Heroe(
					{ 0, 0, 0 },
					sn,
					sm,
					PEARL_NAME + to_string(i * nc + j)
				);
				Vector3 vecH = { 0, 0, H_DEPTH };
				/*auto h = new Heroe(
					vecH,
					mSM->getRootSceneNode()->createChildSceneNode("nHeroe"),
					mSM,
					"Sinbad.mesh");*/
				h->setScale({ 10, 10, 10 });
				h->setRotation({ 0,90,0 });

				h->setPosition({
					LAB_XSET + sWallSize.x * i,
					LAB_YSET + sWallSize.y * j,
					LAB_DEPTH
					});
				h->setScale({ PEARL_SIZE, PEARL_SIZE, PEARL_SIZE });
				hero.push_back(h);
			}
		}
	}

	sLabWidth = sWallSize.x * nf;
	sLabHeight = sWallSize.y * nc;

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
