#pragma once
#include "IG2Object.h"

constexpr double HELIX_RADIUS = 100;

class Blade : public IG2Object
{
public:
	SceneNode* mainNode = nullptr;
	SceneNode* bladeNode = nullptr;
	SceneNode* ogreNode = nullptr;
	Blade(Vector3 initPos, SceneNode* node, SceneManager* sM);
};
