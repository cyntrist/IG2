#pragma once

#include "IG2Object.h"

class Labyrinth;
class Block;


// Clase padre de los villanos que va a implementar sus comportamientos comunes
class Villain : public IG2Object
{
	Labyrinth* lab = nullptr;

	bool isDead_;

	Vector3 dir;
	Vector3 newDir;
	std::vector<bool> availableDirs { true, true, true, true}; // izq arriba der abajo

public:
	Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab)
		: IG2Object(initPos, node, sceneMng, mesh), lab(lab)
	{
		isDead_ = false;
		dir = {0, 0, 0};
		newDir = {0, 0, 0};
	}

	void init() override
	{
	}

	void frameRendered(const FrameEvent& evt) override;


	void setDead(bool a) { isDead_ = a; }
	bool isDead() const { return isDead_; }
	Vector3 getDir() const { return dir; }

	bool checkMiddle() const;
	bool checkCollisions(Vector3 dir);
	Block* getBlock(Vector3 dir);
};
