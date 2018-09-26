#include "Toy.h"



Toy::Toy(Ogre::SceneNode* scene)
{
	this->scene = scene;
	/*Ogre::Entity* ent = Ogre::SceneManager::createEntity("Sinbad.mesh");

	mSinbadNode = mPlaneNode->createChildSceneNode("nSinbad");
	mSinbadNode->attachObject(ent);*/
}


Toy::~Toy()
{
}
