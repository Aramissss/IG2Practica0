#pragma once
#include "gameObject.h"
class PlaneObject :
	public gameObject
{
private:
	Ogre::SceneNode* mPlaneNode = nullptr;
public:
	PlaneObject(Ogre::SceneNode* _parentNode);
	~PlaneObject();
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
};

