#pragma once
#include "Character.h"
#include "OgreAnimation.h"
#include <OgreKeyFrame.h>

#include "Labyrinth.h"

class HeroIntro : public Character
{
	AnimationState* dance = nullptr;
	AnimationState* walk = nullptr;
	AnimationState* walkTop = nullptr;
	AnimationState* sword = nullptr;
	AnimationState* movement = nullptr;
	Entity* swordR = nullptr;
	Entity* swordL = nullptr;
	int animID = 0;

public:
	HeroIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab = nullptr);
	void update(float t) override;
	void generateTrack(SceneManager* sMng);
	void setAnimState(int id);
	AnimationState* getAnim(const std::string& anim) const { return entity->getAnimationState(anim); }
};
