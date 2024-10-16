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

class Labyrinth;
class Heroe;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    void frameRendered(const Ogre::FrameEvent& evt) override;
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    
    
    Ogre::SceneNode* mSinbadNode = nullptr;
    Ogre::SceneNode* mDragonNode = nullptr;
    Ogre::SceneNode* mSwordNode = nullptr;
    Ogre::SceneNode* mHelmetNode = nullptr;
    Ogre::SceneNode* mHeadNode = nullptr;
    Ogre::SceneNode* mBustNode = nullptr;
    Ogre::SceneNode* mRomanNode = nullptr;
    Ogre::SceneNode* mSnowmanNode = nullptr;
      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    Labyrinth* mLabyrinth = nullptr;
    Ogre::SceneNode* mLabNode = nullptr;
    Heroe* mHeroe = nullptr;
    OgreBites::TextBox* levelInfo = nullptr;
    OgreBites::Label* levelLabel = nullptr;
    Game* game = nullptr;
};

#endif
