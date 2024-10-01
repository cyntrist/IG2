#include "Labyrinth.h"

#include "fstream"
#include "Wall.h"
#include "Pearl.h"

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

				box_size = w->calculateBoxSize();
				w->setPosition({
					LAB_XSET + box_size.x * i,
					LAB_YSET + box_size.y * j,
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
					LAB_XSET + box_size.x * i,
					LAB_YSET + box_size.y * j,
					LAB_DEPTH
				});
				p->setScale({PEARL_SIZE, PEARL_SIZE, PEARL_SIZE});
				pearls.push_back(p);
			}
		}
	}

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
