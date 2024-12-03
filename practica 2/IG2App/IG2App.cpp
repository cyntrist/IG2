#include "IG2App.h"

#include <OgreBitesConfigDialog.h>

#include "Labyrinth.h"
#include "Heroe.h"

using namespace Ogre;
using namespace std;

void IG2App::frameRendered(const FrameEvent& evt)
{
	//InputListener::frameRendered(evt);
	if (!insideIntro)
	{
		levelLabel->setCaption("STAGE: " + StringConverter::toString(game->getStage()));
		levelInfo->clearText();
		levelInfo->appendText("Lives: ");
		levelInfo->appendText(StringConverter::toString(game->getLives()));
		levelInfo->appendText("\nPoints: ");
		levelInfo->appendText(StringConverter::toString(game->getPoints()));
	}

	if (game->getStage() == -1) endGame();
	else if (game->getStage() > currentStage)
	{
		std::cout << "CAMBIA 1 " << std::endl;
		currentStage = game->getStage();
		std::cout << "CAMBIA 2 " << std::endl;
		deleteLabyrinth();
		std::cout << "CAMBIA 3 " << std::endl;
		setUpLabyrinth();
		std::cout << "CAMBIA 4 " << std::endl;
	}

	if (mIntro != nullptr) mIntro->update(evt);
}

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	// ESC key finished the rendering...
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	if (evt.keysym.sym == SDLK_q)
	{
		game->changeStage(game->getStage() + 1);
		game->addLives(1);
		game->addPoints(10);
	}

	// caca culo pedo pis

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

	delete mHeroe;
	mHeroe = nullptr;

	delete game;
	game = nullptr;


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

	// Game:
	game = new Game();

	// Adds the listener for this object
	addInputListener(this);
	setupScene();
}

void IG2App::setupScene()
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

	mCamNode->setPosition(0, 100, 10);
	Quaternion rotation(Degree(180), Vector3::UNIT_Z);
	mCamNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
	cam->rotate(rotation);

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0.7, 0.8, 0.9));

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);


	//------------------------------------------------------------------------
	// Creating the light

	//mSM->setAmbientLight(ColourValue(0.7, 0.8, 0.9));
	light = mSM->createLight("Luz");
	light->setType(Light::LT_DIRECTIONAL);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(light);
	mLightNode->setDirection(Vector3(0, 0, -1));


	//------------------------------------------------------------------------
	// Creating Sinbad
	//Entity* ent = mSM->createEntity("Sinbad.mesh");
	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);
	//mSinbadNode->showBoundingBox(true);
	////mSinbadNode->setPosition(x, y, z);
	//mSinbadNode->setScale(20, 20, 20);
	//------------------------------------------------------------------------


	// -------------- FONDO ---------------------------
	Plane fondoSPACE;
	fondoSPACE.d = 1000;
	fondoSPACE.normal = Vector3::NEGATIVE_UNIT_Y;
	mSM->setSkyPlane(true, fondoSPACE, "zoomSky", 1500, 50, true, 10, 50, 50);


	setUpIntro();
	if (!insideIntro)
		setUpLabyrinth();
}

void IG2App::setUpLabyrinth()
{
	/// GUI ejemplo:
	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	levelLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT,
	                                   "InfoCap", "Stage: ", 100);
	levelInfo = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT,
	                                    "LevelInfo", "GameInfo", 250, 100);
	///

	mLabNode = mSM->getRootSceneNode()->createChildSceneNode("nLabyrinth");
	string p = "../media/labyrinths/stage" + to_string(currentStage);
	p += ".txt";
	mLabyrinth = new Labyrinth(
		mLabNode,
		mSM,
		p
	);
	mLabyrinth->setGame(game);


	addInputListener(mLabyrinth->getHero());

	for (auto v : mLabyrinth->getVillains())
		addInputListener(v);


	/// PLANO
	MeshManager::getSingleton().createPlane(
		"planeFloor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3(0, 0, 1), 0),
		mLabyrinth->getLabSize().x,
		mLabyrinth->getLabSize().y
	);

	Entity* planeEnt = mSM->createEntity("suelo", "planeFloor");
	SceneNode* planeNode = mLabNode->createChildSceneNode("sueloNode");
	//entPlano->setMaterialName("");
	planeNode->setPosition(0, 0, LAB_DEPTH - mLabyrinth->getWallSize().z / 2);
	planeNode->attachObject(planeEnt);
	planeEnt->setMaterialName(mLabyrinth->getMatPlane());
}

void IG2App::hideIntro()
{
	mIntroNode->setVisible(false);
	setUpLabyrinth();
}

void IG2App::deleteLabyrinth()
{
	delete mLabyrinth;
	mLabyrinth = nullptr;
	delete mLabNode;
	mLabNode = nullptr;
	delete mHeroe;
	mHeroe = nullptr;
}

void IG2App::setUpIntro()
{
	mIntroNode = mSM->getRootSceneNode()->createChildSceneNode("nIntro");
	mIntro = new Intro(mSM, mIntroNode, mCamNode);
}

void IG2App::endGame()
{
	getRoot()->queueEndRendering();
}
