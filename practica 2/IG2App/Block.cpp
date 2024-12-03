#include "Block.h"
#include <OgreParticleSystem.h>


bool Block::isDead()
{
	return isDead_;
}

void Block::setDead(bool a)
{
	isDead_ = a;
}

void Block::addParticleSys(SceneNode* p)
{
	pSys.push_back(p);
}

void Block::startEmittingParticleSys(int i, bool a)
{
	// ParticleSystem* p = pSys[i]->getAttachedObject(0);

	//p->setEmitting(a);
}

void Block::startEmittingAllParticleSys(bool a)
{
	for (auto s : pSys)
	{
		//    s->setEmitting(a);
	}
}
