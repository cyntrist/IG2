#pragma once

#include "IG2Object.h"


class Labyrinth;

// Clase padre de los villanos que va a implementar sus comportamientos comunes
class Villain : public IG2Object
{
	Labyrinth* lab = nullptr;

public:
	Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab)
		: IG2Object(initPos, node, sceneMng, mesh), lab(lab)
	{
	}
	void init() override {}
};
