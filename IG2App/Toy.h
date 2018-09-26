#pragma once
#include "IG2App.h"
class Toy
{
private:
	Ogre::SceneNode* scene;
	Ogre::SceneNode* nodeCuello = nullptr;
	Ogre::SceneNode* nodeCuerpo = nullptr;
	Ogre::SceneNode* nodeCabeza = nullptr;
	Ogre::SceneNode* nodeOmbligo = nullptr;
	Ogre::SceneNode* nodeNariz = nullptr;
	Ogre::SceneNode* nodeBoca = nullptr;
	Ogre::SceneNode* nodeOjoI = nullptr;
	Ogre::SceneNode* nodeOjoD = nullptr;

public:
	Toy(Ogre::SceneNode* scene);
	~Toy();
};

