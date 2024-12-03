#include "HeroIntro.h"

HeroIntro::HeroIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
	: Character(initPos, node, sceneMng, "heroIntro", lab)
{
	entity = sceneMng->createEntity("Sinbad.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);
	swrdR = sceneMng->createEntity("Sword.mesh");
	swrdL = sceneMng->createEntity("Sword.mesh");

	entity->attachObjectToBone("Handle.R", swrdR);
	entity->attachObjectToBone("Handle.L", swrdL);

	swrdR->setVisible(false);
	swrdL->setVisible(false);

	generateTrack(sceneMng);

	dance = entity->getAnimationState("Dance");
	walk = entity->getAnimationState("RunBase");
	sword = entity->getAnimationState("DrawSwords");
	topwalk = entity->getAnimationState("RunTop");
}

HeroIntro::~HeroIntro()
{
}

void HeroIntro::frameRendered(const FrameEvent& evt)
{
	switch (idAnim)
	{
	case 0:
		if (dance != nullptr) dance->addTime(evt.timeSinceLastFrame);
		break;
	case 1:
		if (walk != nullptr) walk->addTime(evt.timeSinceLastFrame);
		if (topwalk != nullptr) topwalk->addTime(evt.timeSinceLastFrame);
		if (movement != nullptr) movement->addTime(evt.timeSinceLastFrame);
		break;
	case 2:
		if (sword != nullptr) sword->addTime(evt.timeSinceLastFrame);
		if (walk != nullptr) walk->addTime(evt.timeSinceLastFrame);
		if (topwalk != nullptr) topwalk->addTime(evt.timeSinceLastFrame);
		if (movement != nullptr) movement->addTime(evt.timeSinceLastFrame);
		break;
	default:
		break;
	}
}

void HeroIntro::update(float t)
{
	switch (idAnim)
	{
	case 0:
		if (dance != nullptr) dance->addTime(t);
		break;
	case 1:
		if (walk != nullptr) walk->addTime(t);
		if (topwalk != nullptr) topwalk->addTime(t);
		if (movement != nullptr) movement->addTime(t);
		break;
	case 2:
		if (sword != nullptr) sword->addTime(t);
		if (walk != nullptr) walk->addTime(t);
		if (topwalk != nullptr) topwalk->addTime(t);
		if (movement != nullptr) movement->addTime(t);
		break;
	default:
		break;
	}
}


void HeroIntro::generateTrack(SceneManager* sMng)
{
	// Variables
	int movementLength = 200;
	Real duration = 16.0;
	Vector3 keyframePos(0, 55, 0);
	Vector3 keyframeScale(10, 10, 10);
	Quaternion keyframeRot(0, 0, 0, 0);
	Real durStep = duration / 4.0;

	// Create the animation and track
	Animation* anim = sMng->createAnimation("sinbadWalking", duration);
	anim->setInterpolationMode(Animation::IM_LINEAR);
	//anim->setDefaultRotationInterpolationMode();
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	TransformKeyFrame* kf;

	// Keyframe 0 (Init state)
	kf = track->createNodeKeyFrame(0);
	keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(0.5);
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// Keyframe 1: Go to the right
	kf = track->createNodeKeyFrame(4);
	keyframePos += Vector3::UNIT_X * movementLength;
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(4.25);
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(4.75);
	keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// Keyframe 2: Go to the initial position
	kf = track->createNodeKeyFrame(8);
	keyframePos += Vector3::NEGATIVE_UNIT_X * movementLength;
	//keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);


	// Keyframe 3: Go to the left
	kf = track->createNodeKeyFrame(12);
	keyframePos += Vector3::NEGATIVE_UNIT_X * movementLength;
	kf->setRotation(keyframeRot);
	kf->setScale(keyframeScale);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(12.25);
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(12.75);
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// Keyframe 4: Go to the right (initital position)
	kf = track->createNodeKeyFrame(15.5);
	keyframePos += Vector3::UNIT_X * movementLength;
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

	// TURN KEYFRAME
	kf = track->createNodeKeyFrame(16);
	keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);

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
		sword->setEnabled(false);
		topwalk->setLoop(false);
		topwalk->setEnabled(false);
		swrdR->setVisible(false);
		swrdL->setVisible(false);
		break;
	case 1:
		dance->setLoop(false);
		dance->setEnabled(false);
		walk->setLoop(true);
		walk->setEnabled(true);
		movement->setLoop(true);
		movement->setEnabled(true);
		topwalk->setLoop(true);
		topwalk->setEnabled(true);
		break;
	case 2:
		swrdR->setVisible(true);
		swrdL->setVisible(true);
		sword->setLoop(false);
		sword->setEnabled(true);
	default:
		break;
	}

	idAnim = id;
}
