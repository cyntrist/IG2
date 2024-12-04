#include "OgreHeadIntro.h"


OgreHeadIntro::OgreHeadIntro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Labyrinth* lab)
	: Character(initPos, node, sceneMng, "headIntro", lab)
{
	entity = sceneMng->createEntity("ogrehead.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);

	generateTrack(sceneMng);
	createTrail(sceneMng);

	movement = sceneMng->createAnimationState("ogreHeadWalking");
	movement->setLoop(true);
	movement->setEnabled(true);
}



void OgreHeadIntro::update(float t)
{
	if (movement != nullptr) 
		movement->addTime(t);
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
	Real duration = 20;
	Quaternion keyRot(0, 0, 0, 0);
	Vector3 keyPos(-400, 55, 0);
	Vector3 keyScale(2, 2, 2);

	// Create the animation and track
	Animation* anim = sMng->createAnimation("ogreHeadWalking", duration);
	anim->setInterpolationMode(Animation::IM_LINEAR);
	NodeAnimationTrack* track = anim->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	
	// Keyframe 0 (Init state)
	TransformKeyFrame* kf = track->createNodeKeyFrame(0);
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 1 (follow ogre)
	kf = track->createNodeKeyFrame(7.75);
	keyPos = Vector3(120, 55, 0);
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 2 (Turn head)
	kf = track->createNodeKeyFrame(8);
	keyRot = Quaternion(Degree(-90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 3 (head escapes)
	kf = track->createNodeKeyFrame(16);
	keyPos = Vector3(-300, 55, 0);
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 4 (Turn head)
	kf = track->createNodeKeyFrame(16.5);
	keyRot = Quaternion(Degree(90), Vector3(0, 1, 0));
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);

	// Keyframe 3 (head escapes)
	kf = track->createNodeKeyFrame(20);
	keyPos = Vector3(-50, 55, 0);
	keyScale = Vector3(0, 0, 0);
	kf->setScale(keyScale);
	kf->setRotation(keyRot);
	kf->setTranslate(keyPos);
}
