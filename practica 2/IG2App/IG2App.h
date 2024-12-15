#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>

#include "Game.h"
#include "Intro.h"

class Labyrinth;
class Heroe;


class Aspa {
public:
	Aspa(SceneNode* n, SceneManager* sm, string name);
};

class Helix {
public:
	Helix(SceneNode* n, SceneManager* sm, int j);
};


class IG2App : public OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App")
	{
	}; // new -> setup()
	~IG2App() override
	{
	}; // delete -> shutdown()

protected:
	void frameRendered(const FrameEvent& evt) override;
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override; // InputListener
	void setup() override;
	void shutdown() override;
	virtual void setupScene();
	void setUpLabyrinth();
	void hideIntro();
	void deleteLabyrinth();


	void setUpIntro();

	void endGame();


	// --------------- ESTUDIANDO

	void clock();

	void avion();
	SceneNode* mAvion = nullptr;
	SceneNode* mAspas1 = nullptr;
	SceneNode* mAspas2 = nullptr;

	void SinbadAnim();

	AnimationState* dance = nullptr;
	AnimationState* idle = nullptr;


	SceneNode* mSinbadNode = nullptr;
	SceneNode* mDragonNode = nullptr;
	SceneNode* mSwordNode = nullptr;
	SceneNode* mHelmetNode = nullptr;
	SceneNode* mHeadNode = nullptr;
	SceneNode* mBustNode = nullptr;
	SceneNode* mRomanNode = nullptr;
	SceneNode* mSnowmanNode = nullptr;


	SceneNode* mClock = nullptr;
	SceneNode* mGeneral = nullptr;

	SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;

	Light* light = nullptr;
	SceneNode* mLightParent = nullptr;
	SceneNode* mLightNode = nullptr;

	SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	Labyrinth* mLabyrinth = nullptr;
	SceneNode* mLabNode = nullptr;
	Heroe* mHeroe = nullptr;
	OgreBites::TextBox* levelInfo = nullptr;
	OgreBites::Label* levelLabel = nullptr;
	Game* game = nullptr;

	SceneNode* mIntroNode = nullptr;
	Intro* mIntro = nullptr;
	bool insideIntro = true;
	Camera* cam = nullptr;

	int currentStage = 1;
};

#endif
