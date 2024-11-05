#include "Labyrinth.h"

#include "fstream"
#include "Wall.h"
#include "Pearl.h"
#include "Heroe.h"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "Ogrehead.h"
#include "Bat.h"

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
	file >> matPearl >> matWall >> matPlane;


	// ------------------------- LUCES
	string light;
	int lighttype = 0;
	file >> light;
	if (light == "spotlight") lighttype = 0;
	if (light == "directional") lighttype = 1;


	// reading file
	std::vector<string> grid;
	string row;
	for (int i = 0; i < nf; i++)
	{
		file >> row;
		grid.push_back(row);
	}

	std::vector<Block*> aux;

	// DEBUGGING PARA VER EL MODELO
	//auto h = new Bat(
	//	Vector3(0, 0, 0),
	//	sm->getRootSceneNode()->createChildSceneNode(),
	//	sm,
	//	this);
	//h->setScale({10, 10, 10});
	//villains.push_back(h);

	// parsing data into objects
	for (int j = 0; j < nc; j++)
	{
		for (int i = 0; i < nf; i++)
		{
			switch (grid[i][j])
			{
			case 'x':
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

					aux.push_back(w);
					break;
				}
			case 'o':
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

					//// bounding box
					//Entity* box = sm->createEntity("sphere");

					//p->getAABB() = box.node;

					aux.push_back(p);
				}
				break;
			case 'h':
				{
					auto vecH = Vector3(i, j, H_DEPTH);

					auto h = new Heroe(
						vecH,
						sm->getRootSceneNode()->createChildSceneNode("nHeroe"),
						sm,
						"Sinbad.mesh",
						this,
						10
					);

					h->setScale({10, 10, 10});
					h->setRotation({0, 90, 0});
					h->initLight(lighttype);

					hero.push_back(h);

					auto p = new Pearl(
						{0, 0, 0},
						sn,
						sm,
						PEARL_NAME + to_string(i * nc + j)
					);

					p->setType(Block::TYPE::NONE);
					p->setPass(true);
					aux.push_back(p);
				}
				break;
			case 'v': // ogrehead
				{
					auto pos = Vector3(i, j, H_DEPTH);
					auto v = new Ogrehead(
						pos,
						sm->getRootSceneNode()->createChildSceneNode("nOgre" + std::to_string(j + i)),
						sm,
						this);
					villains.push_back(v);
					v->setRotation({0, 90, 0});

					auto p = new Pearl(
						{0, 0, 0},
						sn,
						sm,
						PEARL_NAME + to_string(i * nc + j)
					);

					p->setType(Block::TYPE::NONE);
					p->setPass(true);
					aux.push_back(p);
					break;
				}
			case 's':
				{
					auto pos = Vector3(i, j, H_DEPTH);
					auto v = new Bat(
						pos,
						sm->getRootSceneNode()->createChildSceneNode("nSpider" + std::to_string(j + i)),
						sm,
						this);
					villains.push_back(v);
					v->setRotation({0, 90, 0});
					v->setScale(Vector3(2, 2, 2));

					auto p = new Pearl(
						{0, 0, 0},
						sn,
						sm,
						PEARL_NAME + to_string(i * nc + j)
					);
					p->setType(Block::TYPE::NONE);
					p->setPass(true);
					aux.push_back(p);
					break;
				}
			default:
				{
					auto p = new Pearl(
						{0, 0, 0},
						sn,
						sm,
						PEARL_NAME + to_string(i * nc + j)
					);

					p->setType(Block::TYPE::NONE);
					p->setPass(true);
					aux.push_back(p);
					break;
				}
			}
		}

		blocks.push_back(aux);
		aux.clear();
	}

	labSize = {wallSize.x * nf, wallSize.y * nc};

	// recoloca el laberinto
	for (auto a : blocks)
	{
		for (auto b : a)
		{
			b->setPosition(
				b->getPosition().x - labSize.x / 2 + wallSize.x / 2,
				b->getPosition().y - labSize.y / 2 + wallSize.y / 2,
				b->getPosition().z
			);

			//char aux;
			//if(b->Type() == Block::TYPE::WALL) aux = 'x';
			//if(b->Type() == Block::TYPE::PEARL) aux = 'o';
			//std::cout << aux;
		}
		//std::cout << std::endl;
	}

	for (auto v : villains)
	{
		v->setPosition(
			v->getPosition().x * wallSize.x - labSize.x / 2 + OGREHEAD_SIZE / 2,
			v->getPosition().y * wallSize.y - labSize.y / 2 + OGREHEAD_SIZE / 2,
			v->getPosition().z
		);
	}

	for (auto v : hero)
	{
		v->setPosition(
			v->getPosition().x * wallSize.x - labSize.x / 2 + HERO_SIZE / 2,
			v->getPosition().y * wallSize.y - labSize.y / 2 + HERO_SIZE / 2,
			v->getPosition().z
		);
	}

	//villains[0]->setPosition(0,0,0);


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

Block* Labyrinth::getBlock(int id)
{
	// ¿?¿?¿?¿

	return nullptr;
}

void Labyrinth::initLight()
{
}
