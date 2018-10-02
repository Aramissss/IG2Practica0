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
class Toy
{
private:
	Ogre::SceneNode* nodeMain = nullptr;
	Ogre::SceneNode* nodeCuello = nullptr;
	Ogre::SceneNode* nodeCuerpo = nullptr;
	Ogre::SceneNode* nodeCabeza = nullptr;
	Ogre::SceneNode* nodeOmbligo = nullptr;
	Ogre::SceneNode* nodeNariz = nullptr;
	Ogre::SceneNode* nodeBoca = nullptr;
	Ogre::SceneNode* nodeOjoI = nullptr;
	Ogre::SceneNode* nodeOjoD = nullptr;

public:
	void setScale(Ogre::Vector3 scale) {
		nodeCuello->setScale(scale);
	}
	void setPosition(Ogre::Vector3 position) {
		nodeCuello->setPosition(position);
	}
	Toy(Ogre::SceneNode* nodeMain);
	~Toy();
};

