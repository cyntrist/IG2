#pragma once
#include "fstream"
#include "IG2Object.h"
#include "string"
#include "Character.h"
#include "OgreAnimation.h"
#include "OgreAnimationTrack.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <OgreParticleSystem.h>
#include "HeroIntro.h"
#include "OgreHeadIntro.h"
#include <OgreTimer.h>

class Intro
{
	std::vector<Character*> actors;

	SceneNode* introNode = nullptr;
	SceneManager* sMang = nullptr;
	std::vector<ParticleSystem*> vParSys;

	HeroIntro* hero = nullptr;
	OgreHeadIntro* head = nullptr;
	Timer timerHero; 
	SceneNode* mLightNode = nullptr;
	SceneNode* nPlane = nullptr;

public:
	Intro(SceneManager* SM, SceneNode* sNode, SceneNode* cNode);

	void setUpScene(SceneNode* cNode);
	void setVisible(bool vis);
	void createFireParticlesSystems();
	void createCorrosionBall();
	void update(const FrameEvent& evt);
	void createGround();
};
