#include "GameObject.h"
#include "Simulator.h"
#include <exception>

GameObject::GameObject(Ogre::String nym, Ogre::SceneManager* mgr, Simulator* sim){
	name = nym;
	sceneMgr = mgr;
	simulator = sim;
	try{
		rootNode = mgr->getSceneNode(name);
	}
	catch (std::exception& e) {
		rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name);
	}
	shape = NULL;
	motionState = NULL;
	tr.setIdentity();
	mass = 0.0f;
	inertia.setZero();
}

void GameObject::updateTransform() {
	Ogre::Vector3 pos = rootNode->getPosition();
	tr.setOrigin(btVector3(pos.x, pos.y, pos.z));
	Ogre::Quaternion qt = rootNode->getOrientation();
	tr.setRotation(btQuaternion(qt.x, qt.y, qt.z, qt.w));
	if(motionState){
		motionState->updateTransform(tr);
	}
}

void GameObject::addToSimulator() {
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	updateTransform();
	motionState = new OgreMotionState(tr, rootNode);
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	if (mass != 0.0f) 
		shape->calculateLocalInertia(mass, inertia);
	
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
	rbInfo.m_restitution = 0.9f;
    rbInfo.m_friction = 0.1f;
	
    body = new btRigidBody(rbInfo);
    body->setUserPointer(this);
    
    if (kinematic) {
        body->setCollisionFlags(body->getCollisionFlags() | 
        btCollisionObject::CF_KINEMATIC_OBJECT);
        body->setActivationState(DISABLE_DEACTIVATION);
    }

    simID = simulator->addObject(this);
}

btRigidBody* GameObject::getBody(){
	return this->body;
}
