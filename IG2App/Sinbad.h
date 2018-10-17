#pragma once
#include "gameObject.h"
class Sinbad :
	public gameObject
{
private:
	Ogre::SceneNode* mSinbadNode = nullptr;
public:
	//Ogre::SceneNode* getMainNode() { return mSinbadNode; };
	Sinbad(Ogre::SceneNode* _node, Ogre::SceneManager* _msm);
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	~Sinbad();
};

