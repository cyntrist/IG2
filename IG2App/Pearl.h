#pragma once

#include "IG2Object.h"
#include "Block.h"

class Pearl : public Block
{
	void init() override
	{
	};

public:
	Pearl(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
		: Block(initPos, node->createChildSceneNode(name), sceneMng, PEARL_MESH)
	{
	}
	~Pearl() override = default;
};
