#include "IG2Object.h"

#include <OgreParticleSystem.h>

// Init the static vector for listeners
std::vector<IG2Object*> IG2Object::appListeners = std::vector<IG2Object*>(0, nullptr);


IG2Object::IG2Object() : mNode(nullptr), mSM(nullptr)
{
	this->initialPosition = Vector3::ZERO;
}

IG2Object::IG2Object(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: mNode(node), mSM(sceneMng), initialPosition(initPos)
{
	this->setPosition(initialPosition);
}

IG2Object::IG2Object(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh): mNode(node), mSM(sceneMng),
	initialPosition(initPos)
{
	// Creates a new entity with the mesh and attach the entity
	if (mesh != "")
	{
		entity = sceneMng->createEntity(mesh);
		mNode->attachObject(entity);
	}
	this->setPosition(initialPosition);
}

IG2Object::~IG2Object()
{
	this->removeEntity();

	if (mNode != nullptr)
	{
		mSM->destroySceneNode(mNode);
		mNode = nullptr;
	}

	mSM = nullptr;
}


void IG2Object::setInitialPosition(Vector3 v)
{
	this->initialPosition = v;
}

void IG2Object::move(Vector3 v)
{
	mNode->translate(v);
}

void IG2Object::setPosition(Vector3 v)
{
	mNode->setPosition(v);
}

void IG2Object::setPosition(Real x, Real y, Real z)
{
	mNode->setPosition(Vector3(x, y, z));
}

Vector3 IG2Object::getPosition()
{
	return mNode->getPosition();
}

void IG2Object::setScale(Vector3 vScale)
{
	mNode->setScale(vScale);
}

void IG2Object::setVisible(bool visible)
{
	this->visible = visible;
	mNode->setVisible(visible);
}

void IG2Object::setOrientation(Vector3 vec)
{
	mNode->setDirection(vec.x, vec.y, vec.z, Node::TS_WORLD);
}

void IG2Object::setRotation(Vector3 r)
{
	mNode->roll(Degree(r.x));
	mNode->pitch(Degree(r.y));
	mNode->yaw(Degree(r.z));
}

void IG2Object::updateRotation(int degree)
{
	// cambia la rotacion
	mNode->yaw(Degree(degree));

	// actualiza la direccion actual
}


Vector3 IG2Object::getOrientation()
{
	Vector3 result = mNode->_getDerivedOrientation() * Vector3::UNIT_Z;
	return (Vector3(trunc(result.x), trunc(result.y), trunc(result.z)));
}

void IG2Object::setMaterialName(string materialName)
{
	entity->setMaterialName(materialName);
}

bool IG2Object::hasEntity()
{
	return (entity != nullptr);
}

void IG2Object::removeEntity()
{
	if (hasEntity() && (entity != nullptr))
	{
		mSM->destroyEntity(entity);
		entity = nullptr;
	}
}

Vector3 IG2Object::calculateBoxSize()
{
	Vector3 result;

	if (mNode->getAttachedObjects().size() > 0)
	{
		auto mEntity = static_cast<Entity*>(mNode->getAttachedObject(0));
		const AxisAlignedBox& aab = mEntity->getBoundingBox();
		Vector3 min = aab.getMinimum() * mNode->getScale();
		Vector3 max = aab.getMaximum() * mNode->getScale();
		Real paddingFactor = MeshManager::getSingleton().getBoundsPaddingFactor();

		// adjust min & max to exclude the padding factor..
		Vector3 newMin = min + (max - min) * paddingFactor;
		Vector3 newMax = max + (min - max) * paddingFactor;
		result = newMax - newMin;
	}
	else
		result = {0, 0, 0};

	return result;
}

const AxisAlignedBox& IG2Object::getAABB()
{
	return mNode->_getWorldAABB();
}
