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
#include "gameObject.h"
class Toy : public gameObject
{
private:
	Ogre::SceneNode* nodeCuello = nullptr;
	Ogre::SceneNode* nodeCuerpo = nullptr;
	Ogre::SceneNode* nodeCabeza = nullptr;
	Ogre::SceneNode* nodeOmbligo = nullptr;
	Ogre::SceneNode* nodeNariz = nullptr;
	Ogre::SceneNode* nodeBoca = nullptr;
	Ogre::SceneNode* nodeOjoI = nullptr;
	Ogre::SceneNode* nodeOjoD = nullptr;
	bool parado = true;

public:
	void switchParado() {
		if (parado) parado = false;
		else parado = true;
	}
	void setScale(Ogre::Vector3 scale) {
		nodeCuello->setScale(scale);
	}
	void setPosition(Ogre::Vector3 position) {
		nodeCuello->setPosition(position);
	}
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	Ogre::SceneNode* getMainNode() { return nodeCuello; };
	Toy(Ogre::SceneNode* _node, Ogre::SceneManager* _msm);
	~Toy();
};

