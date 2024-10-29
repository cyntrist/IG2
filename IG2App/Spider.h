#pragma once
#include "Villain.h"

class Spider : public Villain
{
public:
	Spider(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
		: Villain(initPos, node, sceneMng, OGRE_MESH, lab)
	{
		
	}
};

