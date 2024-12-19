#include "HeroIntro.h"

HeroIntro::HeroIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
	: Character(initPos, node, sceneMng, "heroIntro", lab)
{
	entity = sceneMng->createEntity("Sinbad.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);
	swordR = sceneMng->createEntity("Sword.mesh");
	swordL = sceneMng->createEntity("Sword.mesh");

	entity->attachObjectToBone("Handle.R", swordR);
	entity->attachObjectToBone("Handle.L", swordL);

	swordR->setVisible(false);
	swordL->setVisible(false);

	generateTrack(sceneMng);

	dance = entity->getAnimationState("Dance");
	walk = entity->getAnimationState("RunBase");
	sword = entity->getAnimationState("DrawSwords");
	walkTop = entity->getAnimationState("RunTop");
}

void HeroIntro::update(float t)
{
	switch (animID)
	{
	case 0:
		if (dance != nullptr) dance->addTime(t);
		break;
	case 1:
		if (walk != nullptr) walk->addTime(t);
		if (walkTop != nullptr) walkTop->addTime(t);
		if (movement != nullptr) movement->addTime(t);
		break;
	case 2:
		if (sword != nullptr) sword->addTime(t);
		if (walk != nullptr) walk->addTime(t);
		if (walkTop != nullptr) walkTop->addTime(t);
		if (movement != nullptr) movement->addTime(t);
		break;
	default:
		break;
	}
}


void HeroIntro::generateTrack(SceneManager* sMng)
{	
	// Variables
	constexpr int movementLength = 200;
	constexpr Real duration = 16.0;
	Vector3 keyPos(0, 55, 0);
	const Vector3 keyScale(10, 10, 10);
	Quaternion keyRot(0, 0, 0, 0);
	const Real durStep = duration / 4.0;

	// Create the animation and track
	Animation* anim = sMng->createAnimation("sinbadWalking", duration);
	anim->setInterpolationMode(Animation::IM_LINEAR);
	//anim->setDefaultRotationInterpolationMode();
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	TransformKeyFrame* kf;

	// Keyframe 0 (Init state)
	kf = track->createNodeKeyFrame(0);
	keyRot = Quaternion(Degree(0), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(0.5);
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 1: Go to the right
	kf = track->createNodeKeyFrame(4);
	keyPos += Vector3::UNIT_X * movementLength;
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(4.25);
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(4.75);
	keyRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 2: Go to the initial position
	kf = track->createNodeKeyFrame(8);
	keyPos += Vector3::NEGATIVE_UNIT_X * movementLength;
	//keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);


	// Keyframe 3: Go to the left
	kf = track->createNodeKeyFrame(12);
	keyPos += Vector3::NEGATIVE_UNIT_X * movementLength;
	kf->setRotation(keyRot);
	kf->setScale(keyScale);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(12.25);
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(12.75);
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 4: Go to the right (initital position)
	kf = track->createNodeKeyFrame(15.5);
	keyPos += Vector3::UNIT_X * movementLength;
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(16);
	keyRot = Quaternion(Degree(0), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	movement = sMng->createAnimationState("sinbadWalking");
}

void HeroIntro::setAnimState(int id)
{
	switch (id)
	{
	case 0:
		dance->setLoop(true);
		dance->setEnabled(true);
		walk->setLoop(false);
		walk->setEnabled(false);
		walkTop->setLoop(false);
		walkTop->setEnabled(false);
		swordR->setVisible(false);
		swordL->setVisible(false);
		sword->setEnabled(false);
		break;
	case 1:
		dance->setLoop(false);
		dance->setEnabled(false);
		walk->setLoop(true);
		walk->setEnabled(true);
		walkTop->setLoop(true);
		walkTop->setEnabled(true);
		movement->setLoop(true);
		movement->setEnabled(true);
		break;
	case 2:
		swordR->setVisible(true);
		swordL->setVisible(true);
		sword->setLoop(false);
		sword->setEnabled(true);
	default:
		break;
	}

	animID = id;
}
