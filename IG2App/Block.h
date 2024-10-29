#pragma once

#include "IG2Object.h"


class Block : public IG2Object {
public:

	enum TYPE { NONE, WALL, PEARL };


private:
	void init() override
	{
	};

	bool p = false;
	bool isDead_ = false;
	TYPE t = TYPE::NONE;

public:

	Block() {};
	Block(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
		: IG2Object(initPos, node, sceneMng, name) {}

	~Block() override = default;


	void setPass(bool a) { p = a; }
	bool isPass() { return p; }

	void setType(TYPE  a) { t = a; }
	TYPE Type() { return t; }


	bool isDead();
	void setDead(bool a);

};