#pragma once

#include "IG2Object.h"

class Wall : public IG2Object
{
	void init() override
	{
	};

public:
	Wall(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
		: IG2Object(initPos, node->createChildSceneNode(name), sceneMng, WALL_MESH)
	{
	}
	~Wall() override = default;
};

