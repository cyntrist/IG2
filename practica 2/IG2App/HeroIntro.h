#pragma once
#include "Character.h"
#include "OgreAnimation.h"
#include <OgreKeyFrame.h>

#include "Labyrinth.h"

class HeroIntro : public Character
{
	AnimationState* dance = nullptr;
	AnimationState* walk = nullptr;
	AnimationState* topwalk = nullptr;
	AnimationState* sword = nullptr;
	AnimationState* movement = nullptr;

	Entity* swrdR = nullptr;
	Entity* swrdL = nullptr;

	int idAnim = 0;

public:
	HeroIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab = nullptr);
	~HeroIntro() override;
	void update(float t) override;
	AnimationState* getAnim(std::string anim) const { return entity->getAnimationState(anim); }
	void generateTrack(SceneManager* sMng);
	void setAnimState(int id);
};
