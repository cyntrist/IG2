#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>
#include "Block.h"

class Game;


class Labyrinth
{
	int nc, nf;
	std::vector<IG2Object*> hero;
	std::vector<std::vector<Block*>> blocks;
	std::vector<IG2Object*> villains;
	SceneNode node;

	std::string matPearl, matWall, matPlane;

	Vector3 wallSize;
	Vector2 labSize;

	Game* game;

public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();


	std::vector<std::vector<Block*>> getLabyrinth() { return blocks; }
	IG2Object* getHero() const { return hero[0]; }
	Vector2 getLabSize() const { return labSize; }
	Vector3 getWallSize() const { return wallSize; }

	Block* getBlock(int id);
	std::vector<IG2Object*> getVillains() const { return villains; }

	std::string getMatPlane() const { return matPlane; }

	void initLight();

	Block* getBlock(Vector3 pos, Vector3 dir);

	void setVisible(bool vis) const
	{
		//gameNode->setVisible(vis);
		for (auto e : hero)
			e->setVisible(vis);
		for (auto e : blocks)
			for (auto f : e)
				f->setVisible(vis);
		for (auto e : villains)
			e->setVisible(vis);
		
	}

	void setGame(Game* g) { game = g; }
	Game* getGame() const { return game; }
};
