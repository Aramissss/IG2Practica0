#include "PlaneObject.h"



PlaneObject::PlaneObject(Ogre::SceneNode* _parentNode) : gameObject(_parentNode)
{
	

	Ogre::Entity* entPlane = _parentNode->getCreator()->createEntity("mPlane1080x800");
	entPlane->setMaterialName("IG2App/plano");
	mPlaneNode = _parentNode->createChildSceneNode("mPlane1080x800");
	mPlaneNode->attachObject(entPlane);

	mainNode = mPlaneNode;
}
bool PlaneObject::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_p) {
		mainNode->pitch(Ogre::Radian(0.1));
	}
	return true;
}


PlaneObject::~PlaneObject()
{
}
