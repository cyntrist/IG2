#include "IG2App.h"

#include <OgreBitesConfigDialog.h>

#include "Labyrinth.h"
#include "Heroe.h"

using namespace Ogre;
using namespace std;



Aspa::Aspa(SceneNode* n, SceneManager* sm, string name)
{
	Entity* obj = sm->createEntity("cube.mesh");
	SceneNode* nbase = n->createChildSceneNode(name + "base");
	nbase->attachObject(obj);
	nbase->setScale(0.7, 0.01, 0.2);
	nbase->setPosition(-35, 0, 0);
	//

	Entity* head = sm->createEntity("ogrehead.mesh");
	SceneNode* nhead = n->createChildSceneNode(name + "head");
	nhead->attachObject(head);
	nhead->yaw(Degree(-90));
	nhead->roll(Degree(0));
	nhead->pitch(Degree(90));
	nhead->setScale(0.2, 0.2, 0.05);
	nhead->setPosition(-60,-3,0);
	//
}

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




	// ------------------ estudiando -------------------------------

	//idle->addTime();

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

	if (evt.keysym.sym == SDLK_s)
	{
		if (insideIntro)
			hideIntro();
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

	delete mHeroe;
	mHeroe = nullptr;

	delete mIntro;
	mIntro = nullptr;

	delete game;
	game = nullptr;	
	/*
	delete mClock;
	mClock = nullptr;*/


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
	/// GUI ejemplo:
	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	levelLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT,
	                                   "InfoCap", "Stage: ", 100);
	levelInfo = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT,
	                                    "LevelInfo", "GameInfo", 250, 100);
	///
	//------------------------------------------------------------------------
	// Creating the camera

	cam = mSM->createCamera("Cam");
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
	/*Plane fondoSPACE;
	fondoSPACE.d = 1000;
	fondoSPACE.normal = Vector3::NEGATIVE_UNIT_Y;
	mSM->setSkyPlane(true, fondoSPACE, "zoomSky", 1500, 50, true, 10, 50, 50);*/


	//setUpIntro();
	//if (!insideIntro)
	//	setUpLabyrinth();

	clock();

	avion();
}

void IG2App::setUpLabyrinth()
{
	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);
	Quaternion rotation(Degree(-180), Vector3::UNIT_Z);
	cam->rotate(rotation);

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

void IG2App::clock()
{
	// crea el nodo del reloj
	mGeneral = mSM->getRootSceneNode()->createChildSceneNode("general");
	mClock = mGeneral->createChildSceneNode("nClock");

	//// crea las bolitas con sus nodos y las mete en clock
	//Ogre::SceneNode* mHourNode;

	int degrees = 360 / 12;
	int current_degrees = 0;
	int radius = 100;

	// formula de la circumferencia
	double inc = 2 * 3.1415 / 12;
	
	for (int i = 1; i <= 12; i++) {
		cout << "i " << degrees * i << endl;

		Entity* time_part = mSM->createEntity("sphere.mesh");
		string name = "nTime" + to_string(i);
		SceneNode* n_time_part = mClock->createChildSceneNode(name);

		n_time_part->setPosition(cos(inc * i) * radius, sin(inc * i) * radius, -200);

		//// crea la esfera
		n_time_part->attachObject(time_part);

		// posiciona la esfera

		// modifica la escala de la esfera
		if(i%2 == 0)
			n_time_part->setScale(0.15, 0.15 ,0.15);
		else
			n_time_part->setScale(0.1, 0.1, 0.1);

		//// la mete en el clock
		//mClock->addChild(n_time_part);

		current_degrees += degrees;
	}

	// manillas


	SceneNode* manillaS = mGeneral->createChildSceneNode("MANILLAS");

	manillaS->setPosition(0,0,-200);


	SceneNode* manillaGrot = manillaS->createChildSceneNode("nManillaGrot");
	manillaGrot->setPosition(0, 0, 0);
	SceneNode* manillaG = manillaGrot->createChildSceneNode("nManillaG");
	Entity* mG = mSM->createEntity("cube.mesh");
	manillaG->attachObject(mG);
	manillaG->setScale(0.6, 0.08, 0.1);
	manillaG->setPosition(25, 0, 0);
	manillaGrot->roll(Degree(180));

	SceneNode* manillaMrot = manillaS->createChildSceneNode("nManillaMrot");
	manillaMrot->setPosition(0, 0, 0);
	SceneNode* manillaM = manillaMrot->createChildSceneNode("nManillaM");
	Entity* mM = mSM->createEntity("cube.mesh");
	manillaM->attachObject(mM);
	manillaM->setScale(0.6, 0.05, 0.1);
	manillaM->setPosition(25, 0, 0);
	manillaMrot->roll(Degree(0));

	SceneNode* manillaProt = manillaS->createChildSceneNode("nManillaProt");
	manillaProt->setPosition(0,0,0);
	SceneNode* manillaP = manillaProt->createChildSceneNode("nManillaP");
	Entity* mP = mSM->createEntity("cube.mesh");
	manillaP->attachObject(mP);
	manillaP->setScale(0.6, 0.01, 0.1);
	manillaP->setPosition(25,0,0);
	manillaProt->roll(Degree(-90));

}

void IG2App::avion()
{
	mAvion = mSM->getRootSceneNode()->createChildSceneNode("nAvion");

	SceneNode* nbody = mAvion->createChildSceneNode("avion_body");

	// body
	SceneNode* nbarrel = nbody->createChildSceneNode("avion_body_barrel");
	Entity* barrel = mSM->createEntity("sphere.mesh");
	nbarrel->attachObject(barrel);
	nbarrel->setPosition(0,0,0);
	nbarrel->setScale(1.5,0.3,0.3);

	SceneNode* nAla1 = nbody->createChildSceneNode("avion_body_ala1");
	Entity* ala1 = mSM->createEntity("cube.mesh");
	nAla1->attachObject(ala1);
	nAla1->setPosition(0, 0, 50);
	nAla1->setScale(1, 0.05, 0.4);
	nAla1->yaw(Degree(90));

	SceneNode* nAla2 = nbody->createChildSceneNode("avion_body_ala2");
	Entity* ala2 = mSM->createEntity("cube.mesh");
	nAla2->attachObject(ala2);
	nAla2->setPosition(0, 0, -50);
	nAla2->setScale(1, 0.05, 0.4);
	nAla2->yaw(Degree(90));

	SceneNode* ntimon = nbody->createChildSceneNode("avion_body_timon");
	Entity* timon = mSM->createEntity("cube.mesh");
	ntimon->attachObject(timon);
	ntimon->setPosition(-120, -20, 0);
	ntimon->setScale(0.2, 0.4, 0.04);
	ntimon->roll(Degree(-30));

	SceneNode* nNinja = nbody->createChildSceneNode("avion_body_ninja");
	Entity* ninja = mSM->createEntity("penguin.mesh");
	nNinja->attachObject(ninja);
	nNinja->setPosition(70, -30, 0);
	nNinja->setScale(0.5, 0.5, 0.5);
	nNinja->yaw(Degree(-90));
	nNinja->pitch(Degree(180));


	// aspas
	//SceneNode* helix1 = mAvion->createChildSceneNode();
	//Helix(helix1, mSM, 10);
	//helix1->setPosition(0,-100,0);
	//helix1->roll(Degree(0));

	mAvion->setPosition(0,100,-100);


	SinbadAnim();
}

void IG2App::SinbadAnim()
{
	SceneNode* nAnim = mSM->getRootSceneNode()->createChildSceneNode("sinbad_anim_estudiar");
	Entity* sinbadent = mSM->createEntity("Sinbad.mesh");
	nAnim->attachObject(sinbadent);
	nAnim->setPosition(0,0,0);
	nAnim->roll(Degree(180));

	dance = sinbadent->getAnimationState("Dance");
	idle = sinbadent->getAnimationState("IdleBase");

	Animation* idleanim = mSM->createAnimation("IdleBase", 6);
	//idleanim
}

Helix::Helix(SceneNode* n, SceneManager* sm, int j)
{
	float rot = 360 / j;
	for (int i = 0; i < j; i++) {
		SceneNode* naspa1 = n->createChildSceneNode();
		new Aspa(naspa1, sm, "aspa" + to_string(i));
		naspa1->pitch(Degree(0));
		naspa1->yaw(Degree(i * rot));
		naspa1->roll(Degree(0));
	}

	// pinchito
	SceneNode* npincho = n->createChildSceneNode();
	Entity* pincho = sm->createEntity("Barrel.mesh");
	npincho->attachObject(pincho);
	npincho->setPosition(0, 0, 0);
	npincho->setScale(0.5, 0.5, 0.5);

}
