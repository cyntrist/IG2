#include "IG2App.h"

#include <OgreBitesConfigDialog.h>

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

	mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
	Light* luz = mSM->createLight("Luz");
	luz->setType(Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Vector3(-1, 0, -1));


	//------------------------------------------------------------------------
	// Creating Sinbad

	Entity* ent = mSM->createEntity("Sinbad.mesh");
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

	Entity* ent2 = mSM->createEntity("dragon.mesh");
	mDragonNode = mSM->getRootSceneNode()->createChildSceneNode("nDragon");
	mDragonNode->attachObject(ent2);

	// Show bounding box
	mDragonNode->showBoundingBox(false);

	// Set position of Sinbad
	mDragonNode->setPosition(90, 180, 270);

	// Set scale of Sinbad
	mDragonNode->setScale(1, 1, 1);

	mDragonNode->yaw(Degree(-180));
	//mSinbadNode->setVisible(false);

	//------------------------------------------------------------------------
	// Creating sword
	Entity* ent3 = mSM->createEntity("Sword.mesh");
	mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nSword");
	mSwordNode->attachObject(ent3);
	mSwordNode->showBoundingBox(false);
	mSwordNode->setPosition(-10, 155, 140);
	mSwordNode->setScale(20, 20, 20);
	mSwordNode->yaw(Degree(90));
	mSwordNode->roll(Degree(-90));

	//------------------------------------------------------------------------
	// Creating sword
	Entity* ent4 = mSM->createEntity("DamagedHelmet.mesh");
	mHelmetNode = mSM->getRootSceneNode()->createChildSceneNode("nHelmet");
	mHelmetNode->attachObject(ent4);
	mHelmetNode->showBoundingBox(false);
	mHelmetNode->setPosition(-100, -50, 0);
	mHelmetNode->setScale(20, 20, 20);
	mHelmetNode->yaw(Degree(180));

	// Creating sword
	Entity* ent5 = mSM->createEntity("ogrehead.mesh");
	mHeadNode = mSM->getRootSceneNode()->createChildSceneNode("nHead");
	mHeadNode->attachObject(ent5);
	mHeadNode->showBoundingBox(false);
	mHeadNode->setPosition(-100, -100, 0);
	mHeadNode->setScale(1, 1, 1);
	mHeadNode->yaw(Degree(0));

	// Creating sword
	Entity* ent6 = mSM->createEntity("facial.mesh");
	mBustNode = mSM->getRootSceneNode()->createChildSceneNode("nFace");
	mBustNode->attachObject(ent6);
	mBustNode->showBoundingBox(false);
	mBustNode->setPosition(200, -100, 0);
	mBustNode->setScale(5, 5, 5);
	mBustNode->yaw(Degree(0));

	// Creating sword
	Entity* ent7 = mSM->createEntity("RomanBathUpper.mesh");
	mRomanNode = mSM->getRootSceneNode()->createChildSceneNode("nRoman");
	mRomanNode->attachObject(ent7);
	mRomanNode->showBoundingBox(false);
	mRomanNode->setPosition(0, 0, 0);
	mRomanNode->setScale(2, 2, 2);
	mRomanNode->yaw(Degree(0));

	// Creating sword
	Entity* ent8 = mSM->createEntity("RomanBathLower.mesh");
	mRomanNode = mSM->getRootSceneNode()->createChildSceneNode("nLower");
	mRomanNode->attachObject(ent8);
	mRomanNode->showBoundingBox(false);
	mRomanNode->setPosition(0, 0, 0);
	mRomanNode->setScale(2, 2, 2);
	mRomanNode->yaw(Degree(0));

	// Creating sword
	mRomanNode = mSM->getRootSceneNode()->createChildSceneNode("nColumn");
	Entity* ent9 = mSM->createEntity("Columns.mesh");
	mRomanNode->attachObject(ent9);
	mRomanNode->showBoundingBox(false);
	mRomanNode->setPosition(0, 0, 0);
	mRomanNode->setScale(2, 2, 2);
	mRomanNode->yaw(Degree(0));


	///////////////////////// MONYECO DE NIEVE
	// Nodo padre vacío
	mSnowmanNode = mSM->getRootSceneNode()->createChildSceneNode("nSnowman");
	mSnowmanNode->setPosition(0, 0, 300);
	mSnowmanNode->setScale(1, 1, 1);

	// nodos cabeza y cuerpo
	auto head = mSnowmanNode->createChildSceneNode("nCabeza");
	auto eye1 = head->createChildSceneNode("nOjo1");
	auto eye2 = head->createChildSceneNode("nOjo2");
	auto nose = head->createChildSceneNode("nNariz");
	auto mouth = head->createChildSceneNode("nBoca");

	auto body = mSnowmanNode->createChildSceneNode("nCuerpo");
	auto belly = body->createChildSceneNode("nOmbligo");

	Entity* cabeza = mSM->createEntity("sphere.mesh");
	head->attachObject(cabeza);
	head->setPosition(0, 150, 0);
	head->setScale(0.8,0.8,0.8);

	Entity* cuerpo = mSM->createEntity("sphere.mesh");
	body->attachObject(cuerpo);

	int altOjos = 50;
	int profOjos = 100;
	int sepOjos = 20;
	int sS = 1;
	Entity* ojo1 = mSM->createEntity("sphere.mesh");
	eye1->attachObject(ojo1);
	eye1->setPosition(sepOjos,altOjos,profOjos);
	eye1->setScale(sS,sS,sS);

	Entity* ojo2 = mSM->createEntity("sphere.mesh");
	eye2->attachObject(ojo2);
	eye2->setPosition(-sepOjos,altOjos,profOjos);
	eye2->setScale(sS,sS,sS);

	Entity* nariz = mSM->createEntity("sphere.mesh");
	nose->attachObject(nariz);
	//nose->setScale(sS,sS,sS);

	Entity* boca = mSM->createEntity("sphere.mesh");
	mouth->attachObject(boca);
	//mouth->setScale(sS,sS,sS);

	Entity* ombligo = mSM->createEntity("sphere.mesh");
	belly->attachObject(ombligo);
	//belly->setScale(sS,sS,sS);
}
