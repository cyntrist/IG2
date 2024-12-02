#include "OgreHeadIntro.h"

OgreHeadIntro::OgreHeadIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
	: Character(initPos, node, sceneMng, "headIntro", lab)

{
	entity = sceneMng->createEntity("ogrehead.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);

	generateTrack(sceneMng);
	createTrail(sceneMng);
}

OgreHeadIntro::~OgreHeadIntro()
{
}

void OgreHeadIntro::frameRendered(const FrameEvent& evt)
{
	if (movement != nullptr) movement->addTime(evt.timeSinceLastFrame);
}

void OgreHeadIntro::createTrail(SceneManager* sMng)
{
	ParticleSystem* parSys = sMng->createParticleSystem("ogreheadSmokeINTRO", "smokeEstela");
	SceneNode* snTrail = mNode->createChildSceneNode();
	parSys->setEmitting(true);
	snTrail->attachObject(parSys);
}

void OgreHeadIntro::generateTrack(SceneManager* sMng)
{
	// Variables
	int movementLength = 350;
	Real duration = 20;
	Vector3 keyframePos(-300, 55, 0);
	Vector3 keyframeScale(2, 2, 2);
	Quaternion keyframeRot(0, 0, 0, 0);
	Real durStep = duration / 4.0;
	// Create the animation and track
	Animation* anim = sMng->createAnimation("ogreHeadWalking", duration);
	anim->setInterpolationMode(Animation::IM_LINEAR);
	//anim->setDefaultRotationInterpolationMode();
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	TransformKeyFrame* kf;
	// Keyframe 0 (Init state)
	kf = track->createNodeKeyFrame(0);
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	// Keyframe 1 (follow ogre)
	kf = track->createNodeKeyFrame(7.75);
	keyframePos = Vector3(120, 55, 0);
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	// Keyframe 2 (Turn head)
	kf = track->createNodeKeyFrame(8);
	keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	// Keyframe 3 (head escapes)
	kf = track->createNodeKeyFrame(16);
	keyframePos = Vector3(-300, 55, 0);
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	// Keyframe 4 (Turn head)
	kf = track->createNodeKeyFrame(16.5);
	keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	// Keyframe 3 (head escapes)
	kf = track->createNodeKeyFrame(20);
	keyframePos = Vector3(-50, 55, 0);
	keyframeScale = Vector3(0, 0, 0);
	kf->setScale(keyframeScale);
	kf->setRotation(keyframeRot);
	kf->setTranslate(keyframePos);
	movement = sMng->createAnimationState("ogreHeadWalking");
	movement->setLoop(true);
	movement->setEnabled(true);
}
