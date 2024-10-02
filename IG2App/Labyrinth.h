#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>

class Labyrinth
{
	std::vector<IG2Object*> walls;
	std::vector<IG2Object*> pearls;
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
};

