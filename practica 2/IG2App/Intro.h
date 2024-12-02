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

	Camera* introCamera = nullptr;
	std::vector<ParticleSystem*> vParSys;

	Light* introLight = nullptr;

	HeroIntro* hero = nullptr;
	OgreHeadIntro* head = nullptr;
	Timer timerHero; // Timer cambio de animacion
	SceneNode* mLightNode = nullptr;
	SceneNode* nGround = nullptr; // Nodo del suelo.
	AnimationState* animationStateDance = nullptr;

public:
	Intro(SceneManager* SM, SceneNode* sNode, SceneNode* cNode);
	~Intro();

	void setUpScene(SceneNode* cNode);
	void setVisible(bool vis);
	// Crea los fuegos de detras del Hero.
	void createFireParticlesSystems();
	// Crea la trail que le sale al OgreHead.
	//
	// Crea la bola corrosiva de chelo
	void createCorrosionBall();
	void update(const FrameEvent& evt);
	void createGround();
};
