#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>
#include "Block.h"
#include "Villain.h"

class Game;


class Labyrinth
{
	int nc, nf;
	std::vector<IG2Object*> hero;
	std::vector<std::vector<Block*>> blocks;
	std::vector<Villain*> villains;
	SceneNode node;

	std::string matPearl, matWall, matPlane;

	Vector3 wallSize;
	Vector2 labSize;

	Game* game;


	// particluas
	ParticleSystem* psys;

public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();


	std::vector<std::vector<Block*>> getLabyrinth() { return blocks; }
	IG2Object* getHero() const { return hero[0]; }
	Vector2 getLabSize() const { return labSize; }
	Vector3 getWallSize() const { return wallSize; }

	Block* getBlock(int id);
	std::vector<Villain*> getVillains() const { return villains; }

	std::string getMatPlane() const { return matPlane; }

	void initLight();

	Block* getBlock(Vector3 pos, Vector3 dir);



	void setGame(Game* g) { game = g; }
	Game* getGame() { return game; }
};
