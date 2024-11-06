#pragma once
#include "Villain.h"
#include "OgreTimer.h"

constexpr Real BODY_FACTOR = 0.1;
constexpr Real EYE_FACTOR = 0.3;
constexpr Real CAZA_FACTOR = 1.5;
constexpr Real BARREL_FACTOR = 1.5;
constexpr Real ROT_TIMER = 500;
constexpr Real ROT_FACTOR = 0.01f;

class Bat : public Villain
{
	Timer* timer;
	SceneNode* body = nullptr;
	Node* brazoIzq = nullptr;
	Node* brazoDer = nullptr;
	int sentido = 1;
public:
	Bat(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
		: Villain(initPos, node, sceneMng, "", lab)
	{
		// esfera, barrel, RZR-002
		timer = new Timer();

		/// CREACION
		auto head = mNode->createChildSceneNode();
		body = head;
		auto eye1 = head->createChildSceneNode();
		auto eye2 = head->createChildSceneNode();
		auto fang1 = head->createChildSceneNode();
		auto fang2 = head->createChildSceneNode();

		Entity* cabeza = mSM->createEntity("sphere.mesh");
		head->attachObject(cabeza);
		head->setScale(BODY_FACTOR, BODY_FACTOR, BODY_FACTOR);
		Entity* ojo1 = mSM->createEntity("sphere.mesh");
		Entity* ojo2 = mSM->createEntity("sphere.mesh");
		eye1->attachObject(ojo1);
		eye2->attachObject(ojo2);
		eye1->setScale(EYE_FACTOR, EYE_FACTOR, EYE_FACTOR);
		eye2->setScale(EYE_FACTOR, EYE_FACTOR, EYE_FACTOR);
		eye1->setPosition(-75, 5, 80);
		eye2->setPosition(75, 5, 80);

		cabeza->setMaterialName("bat/body");
		ojo1->setMaterialName("bat/eye");
		ojo2->setMaterialName("bat/eye");

		Entity* colm1 = mSM->createEntity("RZR-002.mesh");
		Entity* colm2 = mSM->createEntity("RZR-002.mesh");
		fang1->attachObject(colm1);
		fang2->attachObject(colm2);
		fang1->setScale(CAZA_FACTOR, CAZA_FACTOR, CAZA_FACTOR);
		fang2->setScale(CAZA_FACTOR, CAZA_FACTOR, CAZA_FACTOR);
		fang1->setPosition(-40, -50, 90);
		fang2->setPosition(40, -50, 90);

		auto axis = Vector3(1, 0, 0);
		auto axis2 = Vector3(0, 1, 0);
		fang1->rotate(Quaternion(Radian(-80), axis));
		fang2->rotate(Quaternion(Radian(-80), axis));
		fang1->rotate(Quaternion(Radian(-1), axis2));
		fang2->rotate(Quaternion(Radian(1), axis2));


		auto brazo1 = mNode->createChildSceneNode();
		auto brazo2 = mNode->createChildSceneNode();
		auto b1seg1 = brazo1->createChildSceneNode();
		auto b1seg2 = b1seg1->createChildSceneNode();
		auto b1seg3 = b1seg2->createChildSceneNode();
		auto b2seg1 = brazo2->createChildSceneNode();
		auto b2seg2 = b2seg1->createChildSceneNode();
		auto b2seg3 = b2seg2->createChildSceneNode();

		brazoIzq = brazo1;
		brazoDer = brazo2;

		Entity* b1s1 = mSM->createEntity("Barrel.mesh");
		Entity* b1s2 = mSM->createEntity("Barrel.mesh");
		Entity* b2s1 = mSM->createEntity("Barrel.mesh");
		Entity* b2s2 = mSM->createEntity("Barrel.mesh");
		Entity* b1s3 = mSM->createEntity("RZR-002.mesh");
		Entity* b2s3 = mSM->createEntity("RZR-002.mesh");
		b1seg1->attachObject(b1s1);
		b1seg2->attachObject(b1s2);
		b1seg3->attachObject(b1s3);
		b2seg1->attachObject(b2s1);
		b2seg2->attachObject(b2s2);
		b2seg3->attachObject(b2s3);


		b1seg1->setPosition(10, 5, 0);
		b2seg1->setPosition(-10, 5, 0);
		b1seg1->setScale(1, 3, 1);
		b2seg1->setScale(1, 3, 1);
		b1seg1->rotate(Quaternion(Radian(-1), Vector3(0,0,1)));
		b2seg1->rotate(Quaternion(Radian(1), Vector3(0,0,1)));


		b1seg2->setPosition(10, 3, 0);
		b1seg2->rotate(Quaternion(Radian(1.5), Vector3(0,0,1)));
		//b2seg2->rotate(Quaternion(Radian(-1.5), Vector3(0,0,1)));*/
		b1seg3->rotate(Quaternion(Radian(-0.5), Vector3(0,0,1)));
		b1seg3->setScale(1,0.5,1);
		b1seg3->rotate(Quaternion(Radian(1.2f), Vector3(0,1,0)));
		b1seg3->setPosition(3,-3,2);

		b2seg2->setPosition(-10, 3, 0);
		b2seg2->rotate(Quaternion(Radian(-1.5), Vector3(0,0,1)));
		//b2seg2->rotate(Quaternion(Radian(-1.5), Vector3(0,0,1)));*/
		b2seg3->rotate(Quaternion(Radian(0.5), Vector3(0,0,1)));
		b2seg3->setScale(-1,0.5,1);
		b2seg3->rotate(Quaternion(Radian(-1.2f), Vector3(0,1,0)));
		b2seg3->setPosition(-3,-3,2);
	}

	~Bat() override
	{
		delete timer;
		timer = nullptr;
	}

	void frameRendered(const Ogre::FrameEvent& evt) override
	{
		updateAnim();
		Villain::frameRendered(evt);
		setOrientation(-getDir());
	}

	void setOrientation(Vector3 vec) override
	{
		body->setDirection(vec.x, vec.y, vec.z, Node::TS_WORLD);
	};
	void updateAnim();
};
