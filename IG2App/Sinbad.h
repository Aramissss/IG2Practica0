#pragma once
#include "gameObject.h"
class Sinbad :
	public gameObject
{
private:
	Ogre::SceneNode* mSinbadNode = nullptr;
public:
	Sinbad(Ogre::SceneNode* _parentNode);
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	~Sinbad();
};

