#pragma once
#include "Villain.h"

class Spider : public Villain
{
public:
	Spider(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, Labyrinth* lab)
		: Villain(initPos, node, sceneMng, mesh, lab)
	{
		
	}
};

