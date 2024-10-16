#pragma once
#include "IG2Object.h"



class Block : public IG2Object {
public:
	enum TYPE { NONE, WALL, PEARL, EMPTY };

	TYPE t;

	Block(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name, TYPE t_ = TYPE::NONE) 
		: IG2Object(initPos, node->createChildSceneNode(name), sceneMng, WALL_MESH), t(t_) {}


	TYPE getType() { return t; }
};