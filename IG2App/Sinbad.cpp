#include "Sinbad.h"



Sinbad::Sinbad(Ogre::SceneNode* _node, Ogre::SceneManager* _msm): gameObject(_node)
{
	//mainNode = _parentNode;

	Ogre::Entity* ent = _msm->createEntity("Sinbad.mesh");

	mSinbadNode = _node;
	mSinbadNode->attachObject(ent);

	mSinbadNode->setPosition(400, 100, -300);
	mSinbadNode->setScale(20, 20, 20);
}
bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_DOWN) {
		mSinbadNode->translate({ 0.0,0.0,3.0 }, Ogre::Node::TS_LOCAL);
	}
	return true;
}

Sinbad::~Sinbad()
{
}
