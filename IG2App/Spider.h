#pragma once
#include "Villain.h"

class Spider : public Villain
{
public:
	Spider(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
		: Villain(initPos, node, sceneMng, OGRE_MESH, lab)
	{
		/// CREACION
		//mNode = mSM->getRootSceneNode()->createChildSceneNode();
		//mNode->setPosition(0,0, 0);
		//mNode->setScale(1, 1, 1);

		//auto head = mNode->createChildSceneNode();
		//auto eye1 = head->createChildSceneNode();
		//auto eye2 = head->createChildSceneNode();
		//auto fang1 = head->createChildSceneNode();
		//auto fang2 = head->createChildSceneNode();

		//auto brazo1 = mNode->createChildSceneNode();
		//auto brazo2 = mNode->createChildSceneNode();
		//auto b1seg1 = brazo1->createChildSceneNode();
		//auto b1seg2 = brazo1->createChildSceneNode();
		//auto b1seg3 = brazo1->createChildSceneNode();
		//auto b2seg1 = brazo2->createChildSceneNode();
		//auto b2seg2 = brazo2->createChildSceneNode();
		//auto b2seg3 = brazo2->createChildSceneNode();


		//Entity* cabeza = mSM->createEntity("sphere.mesh");
		//Entity* ojo1 = mSM->createEntity("sphere.mesh");
		//Entity* ojo2 = mSM->createEntity("sphere.mesh");
		//head->attachObject(cabeza);
		//eye1->attachObject(ojo1);
		//eye2->attachObject(ojo2);

		//Entity* cuerpo = mSM->createEntity("sphere.mesh");
		//body->attachObject(cuerpo);

		//int altOjos = 50;
		//int profOjos = 100;
		//int sepOjos = 20;
		//int sS = 1;
		//Entity* ojo1 = mSM->createEntity("sphere.mesh");
		//eye1->attachObject(ojo1);
		//eye1->setPosition(sepOjos, altOjos, profOjos);
		//eye1->setScale(sS, sS, sS);

		//Entity* ojo2 = mSM->createEntity("sphere.mesh");
		//eye2->attachObject(ojo2);
		//eye2->setPosition(-sepOjos, altOjos, profOjos);
		//eye2->setScale(sS, sS, sS);


		//Entity* ombligo = mSM->createEntity("sphere.mesh");
		//belly->attachObject(ombligo);
		////belly->setScale(sS,sS,sS);
	}
};
