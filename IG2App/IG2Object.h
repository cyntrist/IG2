#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMath.h>
#include <OgreFrameListener.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <iostream>
#include "Config.h"

using namespace Ogre;
using namespace std;

class IG2Object : public OgreBites::InputListener {

    public:    
    
        /**
         * Constructor without parameters.
         */
        IG2Object();
    
        /**
         * Constructor.
         * @param initPos Initial position for this element.
         * @param node Scene node for this element.
         * @param sceneMng Scene manager.
         */
        IG2Object(Vector3 initPos, SceneNode *node, SceneManager* sceneMng);
    
        /**
         * Constructor.
         * @param initPos Initial position for this element.
         * @param node Scene node for this element.
         * @param sceneMng Scene manager.
         * @param mesh Mesh that is applied to this element.
         */
        IG2Object(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, String mesh);
        
        /**
         * Destructor
         */
        ~IG2Object();
    
        /**
         * Abtstract method for initialization purposes                 
         */
        virtual void init () = 0;
    
        /**
         * Sets an initial position for this element
         * @param v Vector representing the position of this element.
         */
        void setInitialPosition (Vector3 v);
    
        /**
         * Moves this element.
         * @param v Vector representing the traslation for this element.
         */
        void move (Vector3 v);
    
        /**
         * Sets a position for this element
         * @param v Vector representing the position of this element.
         */
        void setPosition(Vector3 v);
    
        /**
         * Gets the position of this element.
         * @return Position of this element.
         */
        Vector3 getPosition ();
    
        /**
         * Sets the scale for this element.
         * @param v Vector representing the scale for this element.
         */
        void setScale(Vector3 vScale);
    
        /**
         * Sets if this element is visible or not.
         * @param visible If true, the element is visible. The element is not visible otherwise.
         */
        void setVisible (bool visible);
    
        /**
         * Gets the AABB for this element.
         * @return AABB of this element.
         */
        const AxisAlignedBox& getAABB();
    
        /**
         * Gets the orientation for this element.
         * @return Vector representing the orientation for this element.
         */
        Vector3 getOrientation ();
    
        /**
         * Sets the name of the material to be applied to this element.
         * @param materialName Name of the material.
         */
        void setMaterialName (string materialName);
    
        /**
         * Calculates if this element has an attached entity.
         * @return True if this element has an attached entity, or false in another case.
         */
        bool hasEntity ();
    
        /**
         * Removes the entity attached to this element.
         */
        void removeEntity ();
            
        /**
         * Calculates the bounding-box size of the entity
         * @return Vector representing the size of the AABB
         */
        Vector3 calculateBoxSize ();    
    
        /**
         * Adds an IG2Object as listener.
         * @param entidad IG2Object to be added.
         */
        static void addListener(IG2Object* entidad){ appListeners.push_back(entidad); };
                    
    protected:
    
        // Scene node representing this element in the scene
        SceneNode *mNode = nullptr;
    
        // Scene manager
        SceneManager* mSM = nullptr;
    
        // Entity for this element
        Ogre::Entity* entity = nullptr;
    
        // Initial position of this element
        Vector3 initialPosition;
    
        // Static vector of listeners
        static std::vector<IG2Object*> appListeners;
};
