
#ifndef __GameObject_h_
#define __GameObject_h_

#include <btBulletDynamicsCommon.h>
#include "OgreMotionState.h"
#include "BulletContactCallback.h"
#include <Ogre.h>

class Simulator;

class GameObject {
	public:
		Ogre::String name;
        
        CollisionContext* context;
        BulletContactCallback* callback; 	
		btRigidBody* body;

    protected:
		Ogre::SceneManager* sceneMgr;
		Simulator* simulator;
		Ogre::SceneNode* rootNode;
		Ogre::Entity* geom;
		btScalar mass;
		btTransform tr;
		btVector3 inertia;
		OgreMotionState* motionState;

        bool kinematic;
        bool needsUpdates;
        int simID;

    public:
		btCollisionShape* shape;
		GameObject(Ogre::String, Ogre::SceneManager*, Simulator*);
		void updateTransform();
		void addToSimulator();
		btRigidBody* getBody();
        virtual void update(float elapsedTime) {}
}; 

#endif
