#pragma once

#include "IG2Object.h"
#include "Block.h"

class Wall : public Block
{

public:
	void init() override
	{
	};

	Wall(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name);
	~Wall() override = default;
};

