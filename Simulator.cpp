#include "Simulator.h"

int Simulator::nextSimID = 0;

Simulator::Simulator(){
	// Collision configuration contains default setup for memory, collision setup.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	// Use the default collision dispatcher
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. Can also try btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver. For parallel processing you can use different solver.
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(-9.8f, 9.8f, -9.8f));

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
}

Simulator::~Simulator() {

}

int Simulator::addObject (GameObject* o){
	objList.push_back(o);
	//use default collision group/mask values (dynamic/kinematic/static)
	dynamicsWorld->addRigidBody(o->getBody());

    int id = nextSimID++;
    idList.push_back(id);
    return id;
}

bool Simulator::removeObject(GameObject* o) {

}

void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep){
    for (int i = 0; i != objList.size(); i++) {
        idList[i] = 0;
    }
    
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
    
    for (unsigned int i = 0; i < objList.size(); i++) {
        objList[i]->update(elapsedTime);
    }
}

bool Simulator::checkHit(int o) {
    for (int i = idList[o]; i < objList.size(); i++) {
        if (i != o) {
            objList[o]->context->hit = false;
            dynamicsWorld->contactPairTest(
                objList[o]->getBody(), 
                objList[i]->getBody(), 
                *(objList[o]->cCallBack)
                );
            
            if (objList[o]->context->hit) { 
                idList[o] = ++i;
                return true;
            }
        }
    }
    return false;
}
