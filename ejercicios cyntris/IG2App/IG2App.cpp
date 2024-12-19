#include "IG2App.h"

#include "Airplane.h"
#include "Blade.h"
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>

using namespace Ogre;
using namespace std;

// Initial position for the camera
const Vector3 IG2App::CAMERA_INIT_POSITION = {0, 300, 600};

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	// ESC key finished the rendering...
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}

	/// GRAFOS
	else if (evt.keysym.sym == SDLK_s)
	{
		if (clockNode != nullptr)
			clockNode->rotate(Vector3(0, 0, 1), Degree(5));
	}
	else if (evt.keysym.sym == SDLK_a)
	{
		if (clockNode != nullptr)
			clockNode->rotate(Vector3(0, 0, 1), Degree(-5));
	}
	else if (evt.keysym.sym == SDLK_d)
	{
		if (hourHandNodePhantom != nullptr)
			hourHandNodePhantom->rotate(Vector3(0, 0, 1), Degree(5));
	}
	else if (evt.keysym.sym == SDLK_f)
	{
		if (hourHandNodePhantom != nullptr)
			hourHandNodePhantom->rotate(Vector3(0, 0, 1), Degree(-5));
	}
	else if (evt.keysym.sym == SDLK_e)
	{
		if (!attachedLeftSword)
		{
			sinbadEnt->attachObjectToBone("Handle.L", swordLeftEnt);
			attachedLeftSword = true;
		}
		else
		{
			sinbadEnt->detachObjectFromBone(swordLeftEnt);
			attachedLeftSword = false;
		}
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		if (!attachedRightSword)
		{
			sinbadEnt->attachObjectToBone("Handle.R", swordRightEnt);
			attachedRightSword = true;
		}
		else
		{
			sinbadEnt->detachObjectFromBone(swordRightEnt);
			attachedRightSword = false;
		}
	}
	/// FIN GRAFOS


	/// ANIMACIONES

	else if (evt.keysym.sym == SDLK_z)
	{
		if (!isRunning)
		{
			isDancing = !isDancing;

			animationStateDance->setEnabled(isDancing);
			animationStateDance->setLoop(isDancing);
		}
	}
	else if (evt.keysym.sym == SDLK_x)
	{
		if (!isDancing)
		{
			isRunning = !isRunning;

			animationStateRunBase->setEnabled(isRunning);
			animationStateRunTop->setEnabled(isRunning);
			animationStateRunBase->setLoop(isRunning);
			animationStateRunTop->setLoop(isRunning);
		}
	}
	/// FIN ANIMACIONES

	/// EJERCICIO PARTICULAS
	else if (evt.keysym.sym == SDLK_x)
	{
		isEmitting = !isEmitting;
		pSys->setEmitting(isEmitting);
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

void IG2App::setup()
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

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);
	mCamNode->setPosition(CAMERA_INIT_POSITION);
	mCamNode->lookAt(Vector3(0, 0, 0), Node::TS_WORLD);

	// And tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(ColourValue(0.7, 0.8, 0.9));


	//------------------------------------------------------------------------
	// Creating the light (Directional light)

	//mSM->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));

	Light* directionalLight = mSM->createLight("DirectionalLight");
	directionalLight->setType(Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f);

	// Node with the light attached
	SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
	nodeDir->setDirection(Vector3(0, -1, -1));
	nodeDir->attachObject(directionalLight);

	// Setting up the shadows
	//mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);


	//------------------------------------------------------------------------
	//

	/// PLANO
	//MeshManager::getSingleton().createPlane("mPlane1080x800",
	//                                        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                        Plane(Vector3::UNIT_Y, 0),
	//                                        1080, 800, 100, 80,
	//                                        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	//Entity* plane = mSM->createEntity("mPlane1080x800");
	//SceneNode* planeNode = mSM->getRootSceneNode()->createChildSceneNode("sueloNode");
	//planeNode->attachObject(plane);
	////plane->setMaterial();
	///


	/// EJERCICIO CLOCK:
	Entity* ent;
	clockNode = mSM->getRootSceneNode()->createChildSceneNode("clockNode");
	hoursNode = clockNode->createChildSceneNode("hoursNode");

	constexpr double inc = 2 * 3.1415 / 12;
	constexpr int radius = 300;
	for (int i = 1; i <= 12; i++)
	{
		ent = mSM->createEntity("sphere.mesh");
		SceneNode* hourNode = hoursNode->createChildSceneNode("Hora" + std::to_string(i));
		hourNode->attachObject(ent);
		hourNode->setScale(0.4, 0.4, 0.4);
		if (i % 2 == 1)
			hourNode->setScale(0.2, 0.2, 0.2);
		hourNode->setPosition(radius * Math::Cos(inc * i), radius * Math::Sin(inc * i), 0);
	}

	handsNode = clockNode->createChildSceneNode("handsNode");
	hourHandNodePhantom = clockNode->createChildSceneNode("hourHandNodePh");
	hourHandNode = hourHandNodePhantom->createChildSceneNode("hourHandNode");
	minuteHandNode = handsNode->createChildSceneNode("minuteHandNode");
	secondHandNode = handsNode->createChildSceneNode("secondHandNode");

	ent = mSM->createEntity("cube.mesh");
	hourHandNode->attachObject(ent);
	ent = mSM->createEntity("cube.mesh");
	minuteHandNode->attachObject(ent);
	ent = mSM->createEntity("cube.mesh");
	secondHandNode->attachObject(ent);

	hourHandNode->setScale(2, 0.25, 0.02);
	minuteHandNode->setScale(2.5, 0.15, 0.02);
	secondHandNode->setScale(2.5, 0.05, 0.02);

	hourHandNode->translate(radius / 3, 0, 0);
	minuteHandNode->translate(0, radius / 3, 0);
	secondHandNode->translate(0, -radius / 3, 0);

	//hourHandNode->setPosition(radius / 3, 0, 0);
	//minuteHandNode->setPosition(0, radius / 3, 0);
	//secondHandNode->setPosition(0, -radius / 3, 0);

	minuteHandNode->rotate(Vector3(0, 0, 1), Degree(-90));
	secondHandNode->roll(Degree(90));
	clockNode->translate(1000, 0, 0);
	/// FIN EJERCICIO CLOCK


	/// EJERCICIO AVION:
	//auto blade = Blade(Vector3(0,0,0), mSM->getRootSceneNode()->createChildSceneNode(), mSM);
	//auto helix = new Helix(10, mSM, mSM->getRootSceneNode()->createChildSceneNode());

	auto avion = new Airplane(mSM, mSM->getRootSceneNode()->createChildSceneNode());
	avion->setPosition(Vector3(-1500, 0, 0));
	addInputListener(avion);
	/// FIN EJERCICIO AVION


	/// EJERCICIO MATERIALES:
	//MeshManager::getSingleton().createPlane("mPlane1080x800",
	//                                        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                        Plane(Vector3::UNIT_Y, 0),
	//                                        1080, 800, 100, 80,
	//                                        true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	//Entity* plane = mSM->createEntity("mPlane1080x800");
	//SceneNode* planeNode = mSM->getRootSceneNode()->createChildSceneNode("sueloNode");
	//planeNode->attachObject(plane);
	//plane->setMaterialName("ig2/water");

	//auto ogreNod = mSM->getRootSceneNode()->createChildSceneNode("ogreNod");
	//Entity* ent = mSM->createEntity("ogrehead.mesh");
	//ogreNod->attachObject(ent);
	//ogreNod->translate(-50, 40, 0);
	//ogreNod->setScale(2,2,2);

	//auto ogre = new IG2Object(Vector3(-200, 40, 0), mSM->getRootSceneNode()->createChildSceneNode("ogreNode"), mSM,
	//                          "ogrehead.mesh");
	//ogre->setScale(Vector3(2, 2, 2));

	//auto sphere = new IG2Object(Vector3(200, 40, 0), mSM->getRootSceneNode()->createChildSceneNode("sphereNode"), mSM,
	//                            "sphere.mesh");
	//sphere->setScale(Vector3(1, 1, 1));
	//sphere->setMaterialName("ig2/sphere");
	/// FIN EJERCICIO MATERIALES


	/// EJERCICIO ANIMACION:
	//------------------------------------------------------------------------
	// Creating the floor

	//MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                           Plane(Vector3::UNIT_Y, 0),
	//                                           500, 500, 200, 200, true, 1, 1, 1,
	//                                           Vector3::UNIT_Z);
	//   
	//   // Creating the plane
	//   Entity* ent = mSM->createEntity ("exampleFloor", "floor");
	//   ent->setMaterialName("example/materialParaEsteSuelo");
	//   SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	//   floor->attachObject(ent);
	//ent->setMaterialName("example/textureTest");

	//MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                        Plane(Vector3::UNIT_Y, 0),
	//                                        1500, 1500, 200, 200, true, 1, 1, 1,
	//                                        Vector3::UNIT_Z);

	//// Creating the plane
	//Entity* ent = mSM->createEntity("exampleFloor", "floor");
	////ent->setMaterialName("example/stonesFloor");
	//SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	//floor->attachObject(ent);

	//------------------------------------------------------------------------
	// Creating Sinbad

	sinbadEnt = mSM->createEntity("Sinbad.mesh");
	sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
	sinbadNode->attachObject(sinbadEnt);
	sinbadNode->scale(5, 5, 5);
	sinbadNode->setPosition(0, 25, 50); // On the floor!
	sinbadNode->setInitialState();

	// Creating two swords
	swordLeftEnt = mSM->createEntity("Sword.mesh");
	swordRightEnt = mSM->createEntity("Sword.mesh");

	// Obtain the names of all the animations in Sinbad.mesh
	AnimationStateSet* aux = sinbadEnt->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first;
		++it;
		cout << "Animation name (Sinbad.mesh): " << s << endl;
	}

	// Obtain the names of all the bones in Sinbad.mesh
	//    SkeletonInstance * skeleton = sinbadEnt->getSkeleton();
	//    int numBones = skeleton->getNumBones();
	//    for (int i=0; i<numBones; i++){
	//        cout << "Bone name (Sinbad.mesh): " << skeleton->getBone(i)->getName() << endl;
	//    }

	sinbadEnt->attachObjectToBone("Handle.L", swordLeftEnt);
	sinbadEnt->attachObjectToBone("Handle.R", swordRightEnt);
	attachedLeftSword = true;
	attachedRightSword = true;

	//------------------------------------------------------------------------
	// Animation of Sinbad
	animationStateDance = sinbadEnt->getAnimationState("Dance");
	animationStateRunBase = sinbadEnt->getAnimationState("RunBase");
	animationStateRunTop = sinbadEnt->getAnimationState("RunTop");

	isDancing = false;
	isRunning = true;
	animationStateDance->setEnabled(false);
	animationStateRunBase->setEnabled(true);
	animationStateRunTop->setEnabled(true);
	animationStateDance->setLoop(false);
	animationStateRunBase->setLoop(true);
	animationStateRunTop->setLoop(true);

	int movementLength = 30;
	Real duration = 10.0;
	Vector3 keyframePos(0, 25, 0);
	Real durStep = duration / 4.0;
	TransformKeyFrame* kf;
	Quaternion rot(0, 0, 0, 0);

	Animation* anim = mSM->createAnimation("sinbadWalking", duration);
	anim->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(sinbadNode);
	sinbadNode->setInitialState();

	// 0
	kf = track->createNodeKeyFrame(durStep * 0);
	kf->setTranslate(keyframePos);
	rot = Quaternion(Degree(90.0), Vector3::UNIT_Y);
	kf->setRotation(rot);

	// 1
	kf = track->createNodeKeyFrame(durStep * 1);
	keyframePos += Vector3::UNIT_X * movementLength;
	kf->setTranslate(keyframePos);
	rot = Quaternion(Degree(90.0), Vector3::UNIT_Y);
	kf->setRotation(rot);

	// Keyframe 2: Go to the initial position
	kf = track->createNodeKeyFrame(durStep * 2);
	keyframePos += Vector3::NEGATIVE_UNIT_X * movementLength;
	kf->setTranslate(keyframePos);
	rot = Quaternion(Degree(-90.0), Vector3::UNIT_Y);
	kf->setRotation(rot);

	// Keyframe 3: Go to the left
	kf = track->createNodeKeyFrame(durStep * 3);
	keyframePos += Vector3::NEGATIVE_UNIT_X * movementLength;
	kf->setTranslate(keyframePos);
	rot = Quaternion(Degree(-90.0), Vector3::UNIT_Y);
	kf->setRotation(rot);

	// Keyframe 4: Go to the right (initital position)
	kf = track->createNodeKeyFrame(durStep * 4);
	keyframePos += Vector3::UNIT_X * movementLength;
	kf->setTranslate(keyframePos);
	rot = Quaternion(Degree(90.0), Vector3::UNIT_Y);
	kf->setRotation(rot);

	animationState = mSM->createAnimationState("sinbadWalking");
	animationState->setLoop(true);
	animationState->setEnabled(true);
	/// FIN ANIMACION


	/// EJERCICIO PARTICULAS:
	Entity* sphereEnt = mSM->createEntity("sphere.mesh");
	//SceneNode* sphereNode = mSM->getRootSceneNode()->createChildSceneNode();
	//sphereNode->attachObject(sphereEnt);
	//sphereNode->setPosition(Vector3(0, 100, 0));
	//sphereEnt->setMaterialName("example/esferaSmile");

	pSys = mSM->createParticleSystem("psSmoke", "example/smoke");
	pSys->setEmitting(false);
	isEmitting = false;
	//mPSNode = mSM->getRootSceneNode()->createChildSceneNode();
	//mPSNode->setPosition(0,20,0);
	//mPSNode->attachObject(pSys);

	esferaPadreNode = mSM->getRootSceneNode()->createChildSceneNode();
	SceneNode* sphereNode = esferaPadreNode->createChildSceneNode();
	sphereNode->attachObject(sphereEnt);
	sphereNode->setPosition(Vector3(200, 50, 0));
	sphereNode->setScale(0.5, 0.5, 0.5);
	sphereEnt->setMaterialName("example/esferaSmile");

	SceneNode* psysNode = sphereNode->createChildSceneNode();
	psysNode->attachObject(pSys);

	// esto es de andres
	ParticleSystem* psysFuego = mSM->createParticleSystem("psFuego", "example/firePT");
	psysFuego->setEmitting(true);
	SceneNode* psysFuegoNode = mSM->getRootSceneNode()->createChildSceneNode();
	psysFuegoNode->attachObject(psysFuego);
	/// FIN EJERCICIO DE PARTICULAS


	/// EJERCICIO MULTITEXTURAS:
	//MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                           Plane(Vector3::UNIT_Y, 0),
	//                                           500, 500, 200, 200, true, 1, 1, 1,
	//                                           Vector3::UNIT_Z);
	//   
	//   // Creating the plane
	//   Entity* ent = mSM->createEntity ("exampleFloor", "floor");
	//   ent->setMaterialName("example/materialParaEsteSuelo");
	//   SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	//   floor->attachObject(ent);
	//ent->setMaterialName("example/textureTest");

	MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	                                        Plane(Vector3::UNIT_Y, 0),
	                                        1500, 1500, 200, 200, true, 1, 1, 1,
	                                        Vector3::UNIT_Z);

	// Creating the plane
	ent = mSM->createEntity("exampleFloor", "floor");
	//ent->setMaterialName("example/stonesFloor");
	ent->setMaterialName("example/textureBlend");
	SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	floor->attachObject(ent);

	Plane plane;
	plane.d = 1000;
	plane.normal = Vector3::NEGATIVE_UNIT_Y;
	mSM->setSkyPlane(
		true, plane, "example/sky",
		1500, 50, true, 1.5, 50, 50
	);

	MeshManager::getSingleton().createPlane("mirror", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	                                        Plane(Vector3::UNIT_Z, 0),
	                                        500, 500, 200, 200, true, 1, 5, 5,
	                                        Vector3::UNIT_Y);

	Entity* entMirror = mSM->createEntity("exampleMirror", "mirror");
	entMirror->setMaterialName("example/mirror");
	SceneNode* mirrorNode = mSM->getRootSceneNode()->createChildSceneNode();
	mirrorNode->attachObject(entMirror);
	mirrorNode->translate(0, 0, -100);

	Camera* camRef = mSM->createCamera("RefCam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);

	mCamNode->attachObject(camRef);

	auto mpRef = new MovablePlane(Vector3::UNIT_Z, 0);
	mirrorNode->attachObject(mpRef);
	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	TexturePtr rttRef = TextureManager::getSingleton().createManual("rttReflejo",
	                                                                ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	                                                                TEX_TYPE_2D,
	                                                                static_cast<Real>(getRenderWindow()->getViewport(0)
		                                                                ->getActualWidth()),
	                                                                static_cast<Real>(cam->getViewport()->
		                                                                getActualHeight()),
	                                                                0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	TextureUnitState* tu = entMirror->getSubEntity(0)->getMaterial()->
	                                  getTechnique(0)->getPass(0)->createTextureUnitState("rttReflejo");
	tu->setColourOperation(LBO_MODULATE);
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	tu->setProjectiveTexturing(true, camRef);

	renderTexture->addListener(this);
	/// FIN EJERCICIO MULTITEXTURAS


	/// EJERCICIO SHADERS:
	//MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	//                                           Plane(Vector3::UNIT_Y, 0),
	//                                           500, 500, 200, 200, true, 1, 5, 5,
	//                                           Vector3::UNIT_Z);
	//// Creating the plane
	//Entity* ent = mSM->createEntity("exampleFloor", "floor");
	//SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
	//floor->attachObject(ent);
	//ent->setMaterialName("example/stonesFloor

	////Creating a skyplane
	//Plane plane2;
	//plane2.d = 1000;
	//plane2.normal = Vector3::UNIT_Z;

	//// Sky using multitexture
	//mSM->setSkyPlane(true, plane2, "example/spaceSkyShader", 20, 1, true, 0, 50, 50);


	//------------------------------------------------------------------------
	// Primer ejemplo de shader (esfera naranja)

	Entity* sphEnt = mSM->createEntity("uv_sphere.mesh");
	SceneNode* sphNode = mSM->getRootSceneNode()->createChildSceneNode();
	sphNode->attachObject(sphEnt);
	sphNode->setPosition(Vector3(0, 100, 0));
	//sphereEnt->setMaterialName("example/checkeredShader");
	sphEnt->setMaterialName("example/hollowedShader");
}

void IG2App::frameRendered(const FrameEvent& evt)
{
	/// EJERCICIO ANIMACION:
	// Example of numeric value animation (lights)
	//------------------------------------------------------------------------

	//    dynamicComponent = (dynamicComponent + ((int) (evt.timeSinceLastFrame * 1000))) % 3000;
	//    spotLight1->setDiffuseColour(1.0f, dynamicComponent/3000.0, 0.0f);
	//    spotLight2->setDiffuseColour(1.0f, 0.0f, dynamicComponent/3000.0);


	// Example of scene node animation (Sinbad)
	//------------------------------------------------------------------------
	sinbadNode->yaw(Degree(30 * evt.timeSinceLastFrame));

	animationState->addTime(evt.timeSinceLastFrame);

	if (isDancing)
		animationStateDance->addTime(evt.timeSinceLastFrame);
	else if (isRunning)
	{
		animationStateRunBase->addTime(evt.timeSinceLastFrame);
		animationStateRunTop->addTime(evt.timeSinceLastFrame);
	}
	/// FIN ANIMACION


	/// EJERCICIO PARTICULAS:
	if (esferaPadreNode != nullptr)
		esferaPadreNode->rotate(Vector3(0, 1, 0), Degree(5));
	///
}
