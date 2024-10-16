#pragma once

#include "IG2Object.h"


class Block : public IG2Object {
	

	void init() override
	{
	};
public:

	Block() {};
	Block(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
		: IG2Object(initPos, node, sceneMng, name) {}

	~Block() override = default;

};