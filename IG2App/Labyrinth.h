#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>

class Labyrinth
{
	std::vector<IG2Object*> walls;
	std::vector<IG2Object*> pearls;
	std::vector<IG2Object*> hero;
	SceneNode node = nullptr;
public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();


	IG2Object* getHero() { return hero[0]; }
};

