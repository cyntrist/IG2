#include "Labyrinth.h"

#include "fstream"
#include "Wall.h"
#include "Pearl.h"
#include "Heroe.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <OgreParticleSystem.h>

#include "Ogrehead.h"
#include "Bat.h"

Labyrinth::Labyrinth(SceneNode* sn, SceneManager* sm, const string& path) : node(nullptr)
{
	
	startIntro(sn, sm);
	
	// opening stream
	ifstream file(path);
	if (!file.is_open())
	{
		cout << "Error en la lectura del archivo." << endl;
		return;
	}

	// init params
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
					auto vecH = Vector3(0, 0, H_DEPTH);

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
					std::cout << "<<<<<<<:" << h->getPosition() << ":>>>>>>>" << std::endl;
				}
				break;
			case 'v': // ogrehead
				{
					auto pos = Vector3(i, j, H_DEPTH);
					auto v = new Ogrehead(
						pos,
						sm->getRootSceneNode()->createChildSceneNode(
							"nOgrex" + std::to_string(i) + "y" + std::to_string(j)),
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
			case 'b':
				{
					auto pos = Vector3(i, j, H_DEPTH);
					auto v = new Bat(
						pos,
						sm->getRootSceneNode()->createChildSceneNode(
							"nSpiderx" + std::to_string(i) + "y" + std::to_string(j)),
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
			case 's':
			{
				// creacion de smokes
				auto p = new Pearl(
					{ 0, 0, 0 },
					sn,
					sm,
					PEARL_NAME + to_string(i * nc + j)
				);

				p->setPosition({
					wallSize.x * i,
					wallSize.y * j,
					LAB_DEPTH
					});
				p->setScale({ PEARL_SIZE, PEARL_SIZE, PEARL_SIZE });
				p->setType(Block::TYPE::PEARL);
				p->setPass(true);

				//// bounding box
				//Entity* box = sm->createEntity("sphere");

				//p->getAABB() = box.node;

				aux.push_back(p);

				//
				std::string name = "psSmoke" + to_string(i * nc + j);
				ParticleSystem* pSys = sm->createParticleSystem(name, "smokeParticleSystem");
				SceneNode* mPSNode = sm->getRootSceneNode()->createChildSceneNode();
				mPSNode->setPosition(p->getPosition());
				pSys->setEmitting(true);
				mPSNode->attachObject(pSys);
				p->addParticleSys(mPSNode);

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
			std::vector<SceneNode*> aux = b->getParticleSystems();

			for (auto p : aux) {
				p->setPosition(b->getPosition());
			}
		}
	}

	for (auto v : villains)
	{
		v->setPosition(
			v->getPosition().x * wallSize.x - labSize.x / 2 + OGREHEAD_SIZE / 2,
			v->getPosition().y * wallSize.y - labSize.y / 2 + OGREHEAD_SIZE / 2,
			v->getPosition().z
		);

		if(v->GetEstela() != nullptr)
			v->GetEstela()->setPosition(v->getPosition());
	}


	//createFires(sm, Nfires);

	file.close();
}

Labyrinth::~Labyrinth()
{
	hero.clear();

	/*for (const auto i : villains) {
		if(i != nullptr)
		delete i;
	}*/

	villains.clear();
	//for (const auto i : blocks) {
	//	for (const auto j : i) {
	//		if(j != nullptr)
	//		delete j;
	//	}
	//}

	blocks.clear();


	game = nullptr;
}

Block* Labyrinth::getBlock(int id)
{
	// ¿?¿?¿?¿

	return nullptr;
}

void Labyrinth::initLight()
{
}

Block* Labyrinth::getBlock(Vector3 pos, Vector3 dir)
{
	int x = trunc((pos.x + labSize.x / 2) / WALL_LENGTH - 5 + dir.x);
	int y = trunc((pos.y + labSize.y / 2) / WALL_LENGTH - 5 + dir.y);

	std::cout << "GETBLOCKLAB: " << x << " " << y << std::endl;

	if (y >= nc || x >= nf || x < 0 || y < 0)
		return nullptr;

	return blocks[y][x];
}

void Labyrinth::createFires(SceneManager* sm, int n)
{
	int aux = n / 2;
	int diff = 50;
	int posini = -diff * aux;

	for (int i = 0; i < n; i++) {


		// ---------------- fireeeeeeeeeeeeeeeeeee
		std::string name = "fire" + to_string(i);
		ParticleSystem* pSys = sm->createParticleSystem(name, "fireParticleSystem");
		SceneNode* fire = sm->getRootSceneNode()->createChildSceneNode();
		fire->setPosition(Vector3(posini,-10,600));
		pSys->setEmitting(true);
		fire->attachObject(pSys);
		fires.push_back(pSys);
		posini += diff;
	}

}

void Labyrinth::startIntro(SceneNode* sn, SceneManager* sm)
{

	// pone el suelo, a sinbad y al ogrehead
	 
	
	//  -------------------- SINBAD -----------------
	auto vecH = Vector3(0, 0, 700);

	auto h = new Heroe(
		vecH,
		sm->getRootSceneNode()->createChildSceneNode("nHeroeINTRO"),
		sm,
		"Sinbad.mesh",
		this,
		10
	);

	h->setScale({ 10, 10, 10 });
	h->setRotation({ 0, 0, 0 });
	//h->initLight(0);

	hero.push_back(h);

	//  -------------------- OGREHEAD -------------------

	auto pos = Vector3(-100, 0, 700);
	auto v = new Ogrehead(
		pos,
		sm->getRootSceneNode()->createChildSceneNode("nOgrexINTRO"),
		sm,
		this);
	//villains.push_back(v);
	v->setRotation({ 0, 0, 90 });


	// PARTICULAS PLACEHOLDER PARA EL OGREHEAD DE LA INTRO

	std::string name = "ogreheadSmokeINTRO";
	ParticleSystem* pSys = sm->createParticleSystem(name, "smokeEstela");
	SceneNode* estelaNode = sm->getRootSceneNode()->createChildSceneNode();
	estelaNode->setPosition(v->getPosition());
	pSys->setEmitting(true);
	estelaNode->attachObject(pSys);
	v->setEstela(estelaNode);

	//  ---------------------- FLOOR --------------------

	/// PLANO
	MeshManager::getSingleton().createPlane(
		"planeINTRO", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		800, 800, 100, 80,
		true, 1, 1.0, 1.0, Vector3::UNIT_Z
	);

	Entity* planeEnt = sm->createEntity("sueloINTRO", "planeINTRO");
	SceneNode* planeNode = sn->createChildSceneNode("sueloNodeINTRO");
	//entPlano->setMaterialName("");
	planeNode->setPosition(0, -50, 700);
	planeNode->attachObject(planeEnt);
	planeEnt->setMaterialName(getMatPlane());


	// --------------------- FIRE ------------------------------
	createFires(sm, 10);

}

