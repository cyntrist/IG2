#pragma once

#include "IG2Object.h"


class Muro : public IG2Object
{
	void init() override;
public:
	Muro(const Vector3& initPos, SceneNode *node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng, "cube.mesh") { }
};

