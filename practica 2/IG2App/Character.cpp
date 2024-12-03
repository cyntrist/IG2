#include "Character.h"
#include "Labyrinth.h"

Character::Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string name, Labyrinth* lab)
	: IG2Object(initPos, node->createChildSceneNode(name), sceneMng), laberynth(lab)
{
}

Character::~Character()
{
}

void Character::frameRendered(const FrameEvent& evt)
{
}

void Character::update(float t)
{
}

//bool Character::isCenter()
//{
//	int x, y, z;
//	x = mNode->getPosition().x;
//	y = mNode->getPosition().y;
//	z = mNode->getPosition().z;
//
//	Vector3 centro(x % 98, y % 98, z % 98);
//
//	if (centro == Vector3().ZERO)
//		return true;
//	return false;
//}
//
//void Character::rotate()
//{
//	Quaternion q = this->getOrientation().getRotationTo(rotateDirection);
//	mNode->rotate(q);
//	direction = rotateDirection;
//}
