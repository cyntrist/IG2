#include "Intro.h"

Intro::Intro(SceneManager* SM, SceneNode* sNode, SceneNode* cNode)
	: introNode(sNode), sMang(SM)
{
	setUpScene(cNode);
}

Intro::~Intro()
{
}

void Intro::setUpScene(SceneNode* cNode)
{
	// posicion de la camara
	cNode->setPosition(0, 90, 600);
	cNode->rotate(Quaternion(Degree(90), Vector3(0, 1, 0)));
	cNode->rotate(Quaternion(Degree(-90), Vector3(1, 0, 0)));
	cNode->rotate(Quaternion(Degree(90), Vector3(0, 0, 1)));

	// Una luz para guiarnos en la oscuridad,
	Light* luz = sMang->createLight("LuzIntro");
	luz->setType(Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	mLightNode = sMang->getRootSceneNode()->createChildSceneNode("nLuzIntro");
	mLightNode->attachObject(luz);
	mLightNode->setDirection(Vector3(0.0, -1.0, 0.0)); // Apunta hacia abajo.

	// Un suelo que pisar,
	createGround();

	// Unos fuegos para calentarnos,
	//createFireParticlesSystems();

	// Un hero para salvarnos,
	hero = new HeroIntro({0, 55, 0}, introNode, sMang);
	hero->setScale({10, 10, 10});
	hero->setAnimState(0);

	// Una cabeza para pensar pensamientos,
	head = new OgreHeadIntro({100, 10, 0}, introNode, sMang);
	head->setScale({2, 2, 2});


	// Y una animacion para alegrarnos el dia.
	hero->setAnimState(0);


	timerHero.reset();
}

void Intro::setVisible(bool vis)
{
	introNode->setVisible(vis);
}

void Intro::update(const FrameEvent& evt)
{
	hero->update(evt.timeSinceLastFrame);

	if (timerHero.getMilliseconds() / 1000 >= 20)
	{
		timerHero.reset(); // reinicio de la animacion
		hero->setAnimState(0);
	}
	else if (timerHero.getMilliseconds() / 1000 >= 8) {
		hero->setAnimState(2); // animacion de sacar las espadas
	}
	else if (timerHero.getMilliseconds() / 1000 >= 4) {
		hero->setAnimState(1); // animacion de moverse y huir
	}
}

void Intro::createGround()
{
	Plane ground(Vector3::UNIT_Y, 0); // Plano con orientacion.

	Ogre::MeshManager::getSingleton().createPlane(
		"groundIntro", // Nombre de la nueva mesh.
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, // Grupo.
		ground, // Plano base.
		1000, 1000, // Tamanyo.
		20, 20, // Segmentos.
		true, 1, // Normales y numTexCoordSet.
		5, 5, // repeticiones de la textura.
		Vector3::UNIT_Z); // Orientacion.


	Entity* eGround = sMang->createEntity("sueloIntro", "groundIntro");
	nGround = introNode->createChildSceneNode("groundNodeIntro");
	nGround->attachObject(eGround);

	nGround->setPosition({ 0, 0, 0 });
	eGround->setMaterialName("plane"); // Material del suelo.
}

void Intro::createFireParticlesSystems()
{
	Vector3 pos{ -150, 10, -300 }; // Posicion del primer fuego.

	for (int i = 0; i < 10; i++)
	{
		ParticleSystem* parSys = sMang->createParticleSystem("fuego" + std::to_string(i), "intro/fire");
		SceneNode* snFire = introNode->createChildSceneNode();
		snFire->setPosition(pos);
		parSys->setEmitting(true);
		snFire->attachObject(parSys);
		// Shhh ganyanada.
		if (i < 5) { snFire->roll(Degree(30)); }
		else { snFire->roll(Degree(-30)); }
		vParSys.push_back(parSys);
		pos.x += 30;
	}
}
