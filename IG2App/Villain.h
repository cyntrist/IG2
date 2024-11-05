#pragma once

#include "IG2Object.h"

class Labyrinth;
class Block;

enum State
{
	CHASE,
	FLEE,
};

// Clase padre de los villanos que va a implementar sus comportamientos comunes
class Villain : public IG2Object
{
	Labyrinth* lab = nullptr;

	State estado = CHASE;
	bool isDead_;

	Vector3 dir;
	Vector3 newdir;

public:
	Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab)
		: IG2Object(initPos, node, sceneMng, mesh), lab(lab)
	{
		isDead_ = false;
		dir = {0, 0, 0};
		newdir = {0, 0, 0};
	}

	void init() override
	{
	}


	void frameRendered(const FrameEvent& evt) override;


	void setDead(bool a) { isDead_ = a; }
	bool isDead() const { return isDead_; }


	bool checkMiddle();
	bool checkCollisions(Vector3 dir);
	Block* getB(Vector3 dir);
};
