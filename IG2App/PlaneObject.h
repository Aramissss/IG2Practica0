#pragma once
#include "gameObject.h"
#include <OgreRenderTargetListener.h>
#include <Ogre.h>
using namespace Ogre;
class PlaneObject :
	public gameObject, public RenderTargetListener
{
private:
	Ogre::SceneNode* mPlaneNode = nullptr;
	Ogre::Entity* entPlane = nullptr;
public:
	Ogre::Entity* getPlaneEntity() { return entPlane; };
	Ogre::SceneNode* getMainNode() { return mPlaneNode; };
	PlaneObject(Ogre::SceneNode* _node);
	~PlaneObject();
	void crearReflejo(Camera* camRef);
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
};

