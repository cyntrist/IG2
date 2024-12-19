#pragma once
#include "Blade.h"
#include "IG2Object.h"

//constexpr double HELIX_RADIUS = 300;
//constexpr double inc = 2 * 3.1415 / 12;


class Helix : public IG2Object
{
public:
	SceneNode* mainNode;
	Real sepAngle = 0;
	SceneNode* cilinderNode;
	std::vector<Blade*> blades;

	Helix(int n, SceneManager* sm, SceneNode* sn, Vector3 pos = {0, 0, 0})
	: IG2Object(pos, sn, sm)
	{
		mainNode = sn;
		sn->setScale(2,2,2);

		// blades
		sepAngle = 360 / n;
		Real inc = 2 * Math::PI / n;
		for (int i = 0; i < n; i++)
		{
			blades.push_back(new Blade(pos, sn->createChildSceneNode(), sm));
			blades[i]->setPosition(pos + Vector3(HELIX_RADIUS * Math::Cos(inc * i), HELIX_RADIUS * Math::Sin(inc * i), 0));
			blades[i]->roll(Degree(sepAngle * i - 90));
		}

		// cilinder
		cilinderNode = mNode->createChildSceneNode();
		Entity* ent = sm->createEntity("Barrel.mesh");
		cilinderNode->attachObject(ent);
		cilinderNode->setScale(10,10,10);
		cilinderNode->pitch(Degree(90));
	}
};

class Airplane : public IG2Object
{
public:
	SceneNode* pilotNode;
	SceneNode* bodyNode;
	SceneNode* rudderNode;
	SceneNode* leftWingNode;
	SceneNode* rightWingNode;
	SceneNode* leftHelixNode;
	SceneNode* rightHelixNode;

	IG2Object* leftWing;
	IG2Object* rightWing;

	Helix* leftHelix;
	Helix* rightHelix;

	Airplane(SceneManager* sm, SceneNode* sn) : IG2Object(Vector3(0,0,0), sn, sm)
	{
		Entity* ent = sm->createEntity("sphere.mesh");
		bodyNode = mNode->createChildSceneNode();
		bodyNode->attachObject(ent);
		bodyNode->setScale(1.5, 1, 8);

		//ent = sm->createEntity("cube.mesh");
		//leftWingNode = mNode->createChildSceneNode();
		//leftWingNode->attachObject(ent);
		//leftWingNode->setScale(8, 0.5, 2);
		//leftWingNode->translate(300, 0, 0);

		//ent = sm->createEntity("cube.mesh");
		//rightWingNode = mNode->createChildSceneNode();
		//rightWingNode->attachObject(ent);
		//rightWingNode->setScale(8, 0.5, 2);
		//rightWingNode->translate(-300, 0, 0);

		leftWing = new IG2Object(Vector3(300,0,0), mNode->createChildSceneNode(), sm, "cube.mesh");
		leftWing->setScale(Vector3(8, 0.5, 2));

		rightWing = new IG2Object(Vector3(-300,0,0), mNode->createChildSceneNode(), sm, "cube.mesh");
		rightWing->setScale(Vector3(8, 0.5, 2));

		ent = sm->createEntity("ninja.mesh");
		pilotNode = mNode->createChildSceneNode();
		pilotNode->attachObject(ent);
		pilotNode->translate(0, 10, 550);
		pilotNode->setScale(0.8,0.8,0.8);
		pilotNode->yaw(Degree(180));

		ent = sm->createEntity("cube.mesh");
		rudderNode = mNode->createChildSceneNode();
		rudderNode->attachObject(ent);
		rudderNode->translate(0, 40, -680);
		rudderNode->setScale(0.3,1,2);
		rudderNode->pitch(Degree(30));

		leftWingNode = mNode->createChildSceneNode();
		rightWingNode = mNode->createChildSceneNode();
		leftHelix = new Helix(10, sm, leftWingNode);
		rightHelix = new Helix(10, sm, rightWingNode);
		leftWingNode->translate(500,0,100);
		rightWingNode->translate(-500,0,100);
		leftWingNode->setScale(0.7,0.7,0.7);
		rightWingNode->setScale(0.7,0.7,0.7);
	}

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
};
