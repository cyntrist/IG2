#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>
//#include "Block.h"



class Labyrinth
{
	std::vector<Block*> walls;
	std::vector<Block*> pearls;
	std::vector<std::vector<Block*>> blocks;
	std::vector<IG2Object*> hero;
	SceneNode node;

	Vector3 wallSize;
	Vector2 labSize;

public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();


	IG2Object* getHero() { return hero[0]; }
	Vector2 getLabSize() const { return labSize; }
	Vector3 getWallSize() const { return wallSize; }
	Block::TYPE getType(int x, int y) const { 
		
		
		return blocks[x][y]->getType(); }
	Block* getBlock(int x, int y) {
		
	}
};

