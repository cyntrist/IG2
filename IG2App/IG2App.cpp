#include "IG2App.h"

#include <OgreBitesConfigDialog.h>

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(ColourValue(0.7, 0.8, 0.9));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(-1, 0, -1));
    

    
    //------------------------------------------------------------------------
    // Creating Sinbad

    Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);

    // Show bounding box
    mSinbadNode->showBoundingBox(true);
    
    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);
    
    // Set scale of Sinbad
    mSinbadNode->setScale(20, 20, 20);
    
    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    



     //------------------------------------------------------------------------
    // Creating dragon

    Ogre::Entity* ent2 = mSM->createEntity("dragon.mesh");
    mDragonNode = mSM->getRootSceneNode()->createChildSceneNode("nDragon");
    mDragonNode->attachObject(ent2);

    // Show bounding box
    mDragonNode->showBoundingBox(false);

    // Set position of Sinbad
    mDragonNode->setPosition(90, 180, 270);

    // Set scale of Sinbad
    mDragonNode->setScale(1, 1, 1);

    mDragonNode->yaw(Ogre::Degree(-180));
    //mSinbadNode->setVisible(false);

         //------------------------------------------------------------------------
    // Creating sword
	Entity* ent3 = mSM->createEntity("Sword.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nSword");
    mSwordNode->attachObject(ent3);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(-10,155,140);
    mSwordNode->setScale(20, 20, 20);
    mSwordNode->yaw(Ogre::Degree(90));
    mSwordNode->roll(Ogre::Degree(-90));

             //------------------------------------------------------------------------
    // Creating sword
	Entity* ent4 = mSM->createEntity("DamagedHelmet.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nHelmet");
    mSwordNode->attachObject(ent4);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(-100,-50,0);
    mSwordNode->setScale(20, 20, 20);
    mSwordNode->yaw(Ogre::Degree(180));

        // Creating sword
	Entity* ent5 = mSM->createEntity("ogrehead.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nHead");
    mSwordNode->attachObject(ent5);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(-100,-100,0);
    mSwordNode->setScale(1,1,1);
    mSwordNode->yaw(Ogre::Degree(0));

            // Creating sword
	Entity* ent6 = mSM->createEntity("facial.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nFace");
    mSwordNode->attachObject(ent6);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(200,-100,0);
    mSwordNode->setScale(5,5,5);
    mSwordNode->yaw(Ogre::Degree(0));

                // Creating sword
	Entity* ent7 = mSM->createEntity("RomanBathUpper.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nRoman");
    mSwordNode->attachObject(ent7);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(0,0,0);
    mSwordNode->setScale(2,2,2);
    mSwordNode->yaw(Ogre::Degree(0));

    // Creating sword
	Entity* ent8 = mSM->createEntity("RomanBathLower.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nLower");
    mSwordNode->attachObject(ent8);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(0,0,0);
    mSwordNode->setScale(2,2,2);
    mSwordNode->yaw(Ogre::Degree(0));

    // Creating sword
	Entity* ent9 = mSM->createEntity("Columns.mesh");
    mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nColumn");
    mSwordNode->attachObject(ent9);
    mSwordNode->showBoundingBox(false);
    mSwordNode->setPosition(0,0,0);
    mSwordNode->setScale(2,2,2);
    mSwordNode->yaw(Ogre::Degree(0));
}


