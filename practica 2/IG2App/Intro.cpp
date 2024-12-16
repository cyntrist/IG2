#include "Intro.h"

Intro::Intro(SceneManager* SM, SceneNode* sNode, SceneNode* cNode)
	: introNode(sNode), sMang(SM)
{
	setUpScene(cNode);
}

void Intro::setUpScene(SceneNode* cNode)
{
	cNode->setPosition(0, 90, 600);
	cNode->rotate(Quaternion(Degree(90), Vector3(0, 1, 0)));
	cNode->rotate(Quaternion(Degree(-90), Vector3(1, 0, 0)));
	cNode->rotate(Quaternion(Degree(90), Vector3(0, 0, 1)));

	Light* luz = sMang->createLight("LuzIntro");
	luz->setType(Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	mLightNode = sMang->getRootSceneNode()->createChildSceneNode("nLuzIntro");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Vector3(0.0, -1.0, 0.0)); // Apunta hacia abajo.

	createGround();
	createCorrosionBall();
	createFireParticlesSystems();

	hero = new HeroIntro({0, 55, 0}, introNode, sMang);
	hero->setScale({10, 10, 10});
	hero->setAnimState(0);

	head = new OgreHeadIntro({200, 10, 0}, introNode, sMang);
	head->setScale({2, 2, 2});

	timerHero.reset();
}

void Intro::setVisible(bool vis)
{
	introNode->setVisible(vis);
}

void Intro::createCorrosionBall()
{
	Entity* sphereEnt = sMang->createEntity("uv_sphere.mesh");
	SceneNode* sphereNode = introNode->createChildSceneNode();
	sphereNode->attachObject(sphereEnt);
	sphereNode->setPosition(Vector3(0, 75, -200));
	sphereNode->setScale(Vector3(0.8, 0.8, 0.8));
	sphereEnt->setMaterialName("corrosion_material");
}

void Intro::update(const FrameEvent& evt)
{
	hero->update(evt.timeSinceLastFrame);
	head->update(evt.timeSinceLastFrame);

	if (timerHero.getMilliseconds() / 1000 >= 20)
	{
		timerHero.reset(); 
		hero->setAnimState(0);
	}
	else if (timerHero.getMilliseconds() / 1000 >= 4)
		hero->setAnimState(1);
	else if (timerHero.getMilliseconds() / 1000 >= 8)
		hero->setAnimState(2); 
}

void Intro::createGround()
{
	Plane plane(Vector3::UNIT_Y, 0); 

	MeshManager::getSingleton().createPlane(
		"groundIntro", 
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		2000, 2000, 
		50, 50, 
		true, 1, 
		5, 5, 
		Vector3::UNIT_Z);

	Entity* ePlane = sMang->createEntity("sueloIntro", "groundIntro");
	nPlane = introNode->createChildSceneNode("planeIntro");
	nPlane->attachObject(ePlane);
	nPlane->setPosition({0, 0, 0});
	ePlane->setMaterialName("water_material"); // Material del suelo.
}

void Intro::createFireParticlesSystems()
{
	Vector3 pos{55, 25, -300}; // Posicion del primer fuego.
	int n = 10;
	int aux = n / 2;
	int diff = 50;
	pos.x = -diff * aux;
	for (int i = 0; i < n; i++)
	{
		ParticleSystem* parSys = sMang->createParticleSystem("fuego" + 
			std::to_string(i), "fireParticleSystem");
		SceneNode* snFire = introNode->createChildSceneNode();
		snFire->setPosition({pos});
		parSys->setEmitting(true);
		snFire->attachObject(parSys);

		pos.x += diff;

		// Shhh ganyanada.
		/*if (i < 5) { snFire->roll(Degree(30)); }
		else { snFire->roll(Degree(-30)); }
		vParSys.push_back(parSys);
		pos.x += 30;*/
	}
}
