#pragma once
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
class gameObject: public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* parentNode = nullptr;
	Ogre::SceneNode* mainNode = nullptr;
public:
	Ogre::SceneNode* getMainNode() { return mainNode; };
	gameObject(Ogre::SceneNode* _parentNode);
	~gameObject();
};

