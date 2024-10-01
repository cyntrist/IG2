#pragma once

#include "IG2Object.h"

class Pearl : public IG2Object
{
	void init() override
	{
	};

public:
	Pearl(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
		: IG2Object(initPos, node->createChildSceneNode(name), sceneMng, PEARL_MESH)
	{
	}
	~Pearl() override = default;
};
