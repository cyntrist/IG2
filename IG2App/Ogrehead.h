#pragma once
#include "Villain.h"

class Ogrehead : public Villain
{
public:
	Ogrehead(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab)
		: Villain(initPos, node, sceneMng, mesh, lab)
	{
		
	}

};

