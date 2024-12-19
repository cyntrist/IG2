#include "Blade.h"

Blade::Blade(Vector3 initPos, SceneNode* node, SceneManager* sM)
	: IG2Object(initPos, node, sM)
{
	mainNode = node;

	Entity* ent = mSM->createEntity("cube.mesh");
	bladeNode = mNode->createChildSceneNode();
	bladeNode->attachObject(ent);
	//bladeNode->setPosition(0, HELIX_RADIUS / 3, 0);
	bladeNode->setScale(0.4, 2, 0.02);
	
	ogreNode = mNode->createChildSceneNode();
	ent = mSM->createEntity("ogrehead.mesh");
	ogreNode->attachObject(ent);
	ogreNode->setPosition(0, HELIX_RADIUS / 4, 10);
	ogreNode->setScale(0.5, 0.5, 0.5);
}
