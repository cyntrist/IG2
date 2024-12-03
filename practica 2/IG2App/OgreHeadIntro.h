#pragma once
#include "Character.h"
#include "OgreAnimation.h"
#include <OgreKeyFrame.h>
#include <OgreParticleSystem.h>

class OgreHeadIntro : public Character
{
	void generateTrack(SceneManager* sMng);
	AnimationState* movement = nullptr;

public:
	OgreHeadIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab = nullptr);
	~OgreHeadIntro() override;
	void update(float t) override;
	void createTrail(SceneManager* sMng);
};
