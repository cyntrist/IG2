#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
        
    // Running animation
    // TODO...
    
    // Dancing animation
    if (evt.keysym.sym == SDLK_d) {
        animationState = sinbadEnt->getAnimationState("Dance");
        if (!isDancing) {
            animationState->setEnabled(true);
            animationState->setLoop(true);
            isDancing = true;
        }
        else {
            animationState->setEnabled(false);
            animationState->setLoop(false);
            isDancing = false;
        }

    }
    
    // Attach/Dettach right sword
    if (evt.keysym.sym == SDLK_r) {
        if (!attachedRightSword) {
            sinbadEnt->attachObjectToBone("Handle.R", swordRightEnt);
            attachedRightSword = true;
        }
        else {
            sinbadEnt->detachObjectFromBone(swordRightEnt);
            attachedRightSword = false;

        }

    }
    
    // Attach/Dettach left sword
    if (evt.keysym.sym == SDLK_l) {
        if (!attachedLeftSword) {
            sinbadEnt->attachObjectToBone("Handle.L", swordLeftEnt);
            attachedLeftSword = true;
        }
        else {
            sinbadEnt->detachObjectFromBone(swordLeftEnt);
            attachedLeftSword = false;

        }

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
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);
    mCamNode->setPosition(0, 0, 600);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
        
    
    //------------------------------------------------------------------------
    // Creating the floor
    
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            Plane(Vector3::UNIT_Y, 0),
                                            1500, 1500, 200, 200, true, 1, 5, 5,
                                            Vector3::UNIT_Z);
    
    // Creating the plane
    Entity* ent = mSM->createEntity ("exampleFloor", "floor");
    ent->setMaterialName("example/stonesFloor");
    SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
    floor->attachObject(ent);
    
    
    //------------------------------------------------------------------------
    // Creating the light (Directional light)

    Ogre::Light* directionalLight1 = mSM->createLight("DirectionalLight1");
    directionalLight1->setType(Light::LT_DIRECTIONAL);
    directionalLight1->setDiffuseColour(1.0f,1.0f,1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(directionalLight1);
    
    // Setting up the shadows
    //mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    
    
    //------------------------------------------------------------------------
    // Creating the light (Spot light) -> Just for checking the numeric value animation
    
    // The light
//    spotLight1 = mSM->createLight("SpotLight1");
//    spotLight1->setType(Light::LT_SPOTLIGHT);
//    spotLight1->setDiffuseColour(1.0f, 0.0f, 0.0f);
//    
//    // Node with the light attached
//    nodeSpot1 = mSM->getRootSceneNode()->createChildSceneNode();
//    nodeSpot1->setPosition(100,200,0);
//    nodeSpot1->setDirection(Ogre::Vector3(0,-1,0));
//    nodeSpot1->attachObject(spotLight1);
//    
//    spotLight2 = mSM->createLight("SpotLight2");
//    spotLight2->setType(Light::LT_SPOTLIGHT);
//    spotLight2->setDiffuseColour(0.0f, 1.0f, 0.0f);
//
//    // Node with the light attached
//    nodeSpot2 = mSM->getRootSceneNode()->createChildSceneNode();
//    nodeSpot2->setPosition(0,200,0);
//    nodeSpot2->setDirection(Ogre::Vector3(0,-1,0));
//    nodeSpot2->attachObject(spotLight2);
    
        
    //------------------------------------------------------------------------
    // Creating Sinbad
    
    sinbadEnt = mSM->createEntity("Sinbad.mesh");
    sinbadNode =  mSM->getRootSceneNode()->createChildSceneNode();
    sinbadNode->attachObject(sinbadEnt);
    sinbadNode->scale(5, 5, 5);
    sinbadNode->setPosition(0, 25, 0); // On the floor!
    sinbadNode->setInitialState();
    
    // Creating two swords
    swordLeftEnt = mSM->createEntity("Sword.mesh");
    swordRightEnt = mSM->createEntity("Sword.mesh");
     
    // Obtain the names of all the animations in Sinbad.mesh
//    AnimationStateSet * aux = sinbadEnt->getAllAnimationStates();
//    auto it = aux->getAnimationStateIterator().begin();
//    while (it != aux->getAnimationStateIterator().end()){
//        auto s = it->first;
//        ++it;
//        cout << "Animation name (Sinbad.mesh): " << s << endl;
//    }
    
    // Obtain the names of all the bones in Sinbad.mesh
//    SkeletonInstance * skeleton = sinbadEnt->getSkeleton();
//    int numBones = skeleton->getNumBones();
//    for (int i=0; i<numBones; i++){
//        cout << "Bone name (Sinbad.mesh): " << skeleton->getBone(i)->getName() << endl;
//    }

    
    //------------------------------------------------------------------------
    // Animation of Sinbad
    // TODO...
    
    // Set keyframes here...
    // TODO...
    
    // Our defined animation
    // TODO...
    
    // Animations for running and dancing...
    // TODO...
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt){
        
    // Example of numeric value animation (lights)
    //------------------------------------------------------------------------
    
//    dynamicComponent = (dynamicComponent + ((int) (evt.timeSinceLastFrame * 1000))) % 3000;
//    spotLight1->setDiffuseColour(1.0f, dynamicComponent/3000.0, 0.0f);
//    spotLight2->setDiffuseColour(1.0f, 0.0f, dynamicComponent/3000.0);
        
    
    // Example of scene node animation (Sinbad)
    //------------------------------------------------------------------------
    //sinbadNode->yaw(Ogre::Degree(30 * evt.timeSinceLastFrame));
        
    
    // Example of NodeAnimationTrack
    //------------------------------------------------------------------------
    // TODO...
    
    
    // Example of Sinbad's animation (running and dancing)
    //------------------------------------------------------------------------
    //sinbadEnt->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);

    if(animationState != nullptr)
        animationState->addTime(evt.timeSinceLastFrame);
    
}

