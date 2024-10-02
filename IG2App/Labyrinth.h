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
	Vector3 box_size = { WALL_SIZE, WALL_SIZE, WALL_SIZE };
public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();
};

