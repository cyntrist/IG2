#include "IG2App.h"

#include <OgreBitesConfigDialog.h>

#include "Labyrinth.h"
#include "Heroe.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	// ESC key finished the rendering...
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	return true;
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;
	mTrayMgr = nullptr;
	delete mCamMgr;
	mCamMgr = nullptr;

	delete mLabyrinth;
	mLabyrinth = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
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

void IG2App::setupScene(void)
{
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
	mCamNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0.7, 0.8, 0.9));

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);


	//------------------------------------------------------------------------
	// Creating the light

	//mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
	Light* luz = mSM->createLight("Luz");
	luz->setType(Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Vector3(-1, 0, -1));


	//------------------------------------------------------------------------
	// Creating Sinbad
	//Entity* ent = mSM->createEntity("Sinbad.mesh");
	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);
	//mSinbadNode->showBoundingBox(true);
	////mSinbadNode->setPosition(x, y, z);
	//mSinbadNode->setScale(20, 20, 20);
	//------------------------------------------------------------------------

	mLabyrinth = new Labyrinth(
		mSM->getRootSceneNode()->createChildSceneNode("nLabyrinth"), 
		mSM
	);


	// --------- Crea al HEROE ---------------
	Vector3 vecH = {0, 0, 0};
	mHeroe = new Heroe(
		vecH, 
		mSM->getRootSceneNode()->createChildSceneNode("nHeroe"), 
		mSM, 
		"Sinbad.mesh");

	// añade como listener al heroe
	addInputListener(mHeroe);


}
