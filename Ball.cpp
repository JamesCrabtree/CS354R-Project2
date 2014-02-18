#include <iostream>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "Ball.h"

Ball::Ball(
    Ogre::String nym, 
    Ogre::SceneManager* mgr, 
    Simulator* sim, 
    float radius, 
    float m, 
    Ogre::Vector3 pos, 
    float restitution, 
    float friction
    ) 
: GameObject(nym, mgr, sim)
{
    geom = mgr->createEntity(name, "sphere.mesh");
    geom->setCastShadows(true);
    rootNode->attachObject(geom);

    // sphere starts at 100 units radius
    rootNode->scale(
        radius * 0.01f,
        radius * 0.01f,
        radius * 0.01f
        );

    rootNode->setPosition(pos);

    shape = new btSphereShape(radius);
    mass = m;
}

void Ball::update(float elapsedTime) {
    while (simulator->checkHit(simID)) {
        if (context->velNorm > 5.0 || context->velNorm < -5.0) {
            if (context->theObject->name != name) {
                std::cout << "bounce!" << std::endl;
            }
        }
    }
}
