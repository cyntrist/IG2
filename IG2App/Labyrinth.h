#pragma once

#include "IG2Object.h"
#include "string"
#include <vector>
#include "Block.h"


///
/// TO DO:	CAMBIAR COLISIONES DE PERLAS DE INDICE A AABB
///			TEXTURAS, MODIFICAR EL STAGE1.TXT Y AÑADIR LAS TEXTURAS A MEDIA/IG2APP
///			COLISIONES DE VILLANOS Y SINBAD CON AABB
/// 



class Labyrinth
{
	std::vector<IG2Object*> walls;
	std::vector<IG2Object*> pearls;
	std::vector<IG2Object*> hero;
	//std::vector<Block*> blocks;
	std::vector<std::vector<Block*>> blocks;
	std::vector<IG2Object*> villains;
	SceneNode node;

	Vector3 wallSize;
	Vector2 labSize;

public:
	Labyrinth(SceneNode* sn, SceneManager* sm, const string& path = LAB_PATH);
	~Labyrinth();


	std::vector<std::vector<Block*>> getLabyrinth() { return blocks; }
	IG2Object* getHero() const { return hero[0]; }
	Vector2 getLabSize() const { return labSize; }
	Vector3 getWallSize() const { return wallSize; }

	Block* getBlock(int id);
	std::vector<IG2Object*> getVillains() const { return villains; }

	void initLight();
};

