#pragma once

#include "IG2Object.h"

class Labyrinth;


class Character : public IG2Object
{
protected:
	Vector3 direction{ 0,0,0 };
	int vel = 1;
	Vector3 rotateDirection{ 0,0,0 };
	Labyrinth* laberynth = nullptr;

	bool visible = true;
public:

	Character() : IG2Object(), laberynth(nullptr) {}
	Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string name = "hero", Labyrinth* lab = nullptr);
	~Character();

	void init() override {}

	void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual void update(float t);
	bool isCenter();

	void rotate();
};