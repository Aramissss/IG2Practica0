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
#include <vector>
#include <iostream>
enum gameObjectEvent{BOMBAEXPLOTA};

class gameObject: public OgreBites::InputListener
{
	
protected:
	Ogre::SceneNode* mNode = nullptr;
	
public:	

	virtual void handleEvent(gameObjectEvent ev) {};
	void fireAppEvent(gameObjectEvent ev);
	static void addAppListener(gameObject * go);
	Ogre::SceneNode* getMainNode() { return mNode; };
	gameObject(Ogre::SceneNode* _node);
	~gameObject();
};

static std::vector<gameObject*> appListeners;