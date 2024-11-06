#include "Wall.h"

Wall::Wall(const Vector3& initPos, SceneNode* node, SceneManager* sceneMng, std::string name, std::string material)
	: Block(initPos, node->createChildSceneNode(name), sceneMng, WALL_MESH)
{
	setMaterialName(material);
}
