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
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include <sstream>
#include <iostream>
#include <string>
#include <OgreRenderTargetListener.h>
//#include "DataSizes.h"

class IG2App : public OgreBites::IG2ApplicationContext, OgreBites::InputListener, Ogre::RenderTargetListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App")
	{
	};

	~IG2App() override
	{
	};

protected:
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void shutdown() override;
	void setup() override;
	virtual void setupScene();
	void frameRendered(const Ogre::FrameEvent& evt) override;

private:
	static const Ogre::Vector3 CAMERA_INIT_POSITION;

	// Scene manager and tray system
	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;

	// Camera
	Ogre::SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	/// EJERCICIO GRAFOS
	Ogre::SceneNode* clockNode;
	Ogre::SceneNode* hoursNode;
	Ogre::SceneNode* handsNode;
	Ogre::SceneNode* hourHandNode;
	Ogre::SceneNode* hourHandNodePhantom;
	Ogre::SceneNode* minuteHandNode;
	Ogre::SceneNode* secondHandNode;

	/// EJERCICIO ANIMACIONES
	// Sinbad and swords
	Ogre::SceneNode* sinbadNode = nullptr;
	Ogre::Entity* sinbadEnt;
	Ogre::Entity* swordLeftEnt;
	Ogre::Entity* swordRightEnt;

	// Flags to control the attached swords
	bool attachedLeftSword = false;
	bool attachedRightSword = false;

	// Lights
	Ogre::Light* spotLight1;
	Ogre::Light* spotLight2;
	Ogre::SceneNode* nodeSpot1 = nullptr;
	Ogre::SceneNode* nodeSpot2 = nullptr;
	int dynamicComponent = 0;

	// Animation state
	Ogre::AnimationState* animationState;

	// Animation states for Sinbad
	Ogre::AnimationState* animationStateDance;
	Ogre::AnimationState* animationStateRunBase;
	Ogre::AnimationState* animationStateRunTop;

	// Flags to control the animations
	bool isDancing = false;
	bool isRunning = false;


	/// EJERCICIO PARTICULAS
	bool isEmitting = false;
	Ogre::SceneNode* mPSNode;
	Ogre::ParticleSystem* pSys;
	Ogre::SceneNode* esferaPadreNode;
};

#endif
