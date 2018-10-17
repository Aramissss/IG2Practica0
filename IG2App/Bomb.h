#pragma once
#include "gameObject.h"
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreAnimationState.h>
using namespace Ogre;
class Bomb: public gameObject
{
private:
	Ogre::SceneNode* mBombNode = nullptr;
public:
	AnimationState * animationState;
	void setPosition(Ogre::Vector3 position) {
		//mBombNode->setPosition(position);
	}
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	Bomb(Ogre::SceneNode* _node, Ogre::SceneManager* _msm);
	~Bomb();
};

