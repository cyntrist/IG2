#pragma once

#include "IG2Object.h"
#include "Block.h"

class Wall : public Block
{
	void init() override
	{
	};

public:
	Wall(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name, Block::TYPE t_)
		: Block(initPos, node->createChildSceneNode(name), sceneMng, WALL_MESH, t_)
	{
	}
	~Wall() override = default;
};

