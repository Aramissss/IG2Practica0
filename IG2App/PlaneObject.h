#pragma once
#include "gameObject.h"
class PlaneObject :
	public gameObject
{
private:
	Ogre::SceneNode* mPlaneNode = nullptr;
	Ogre::Entity* entPlane = nullptr;
public:
	Ogre::Entity* getPlaneEntity() { return entPlane; };
	PlaneObject(Ogre::SceneNode* _parentNode);
	~PlaneObject();
	void crearReflejo();
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
};

