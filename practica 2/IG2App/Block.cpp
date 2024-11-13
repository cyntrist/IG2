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

void Block::addParticleSys(ParticleSystem* p)
{
    pSys.push_back(p);
}

void Block::startEmittingParticleSys(int i, bool a)
{
    pSys[i]->setEmitting(a);
}

void Block::startEmittingAllParticleSys(bool a)
{
    for (auto s : pSys) {
        s->setEmitting(a);
    }
}
