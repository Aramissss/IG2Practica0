#include "gameObject.h"

gameObject::gameObject(Ogre::SceneNode* _node): mNode(_node)
{
}

void gameObject::addAppListener(gameObject * go)
{
	appListeners.push_back(go);
};
void gameObject::fireAppEvent(gameObjectEvent ev)
{
	for (int i = 0; i < appListeners.size(); i++) {

		appListeners[i]->handleEvent(ev);
	}
};

gameObject::~gameObject()
{
}
