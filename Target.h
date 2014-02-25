#pragma once

#include "GameObject.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include "Simulator.h"
#include <Ogre.h>

class Target : public GameObject {
    protected:
        int wall;
        Ogre::Real radius;
        Ogre::Real boxWidth;
        Ogre::Real boxHeight; 
        Ogre::Real boxDepth;
        Ogre::ManualObject* circle;

    public: 
        Target(
            Ogre::String nym, 
            Ogre::SceneManager* mgr, 
            Simulator* sim, 
            Ogre::Real boxX, 
            Ogre::Real boxY, 
            Ogre::Real boxZ, 
            Ogre::Real boxWidth, 
            Ogre::Real boxHeight, 
            Ogre::Real boxDepth,
            Ogre::Real radius
            );
        
        virtual void update();

    protected:
        void setPose(int wall, float x, float y);
};
