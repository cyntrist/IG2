#include "Wall.h"

Wall::Wall(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name)
	: Block(initPos, node->createChildSceneNode(name), sceneMng, WALL_MESH)
{
	setMaterialName("wall");
}
