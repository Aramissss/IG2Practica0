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
	ParticleSystem* smoke = nullptr;
	Entity* ent = nullptr;
	bool exploded = false;
public:
	AnimationState * animationState;
	void setPosition(Ogre::Vector3 position) {
		mBombNode->setPosition(position);
	}
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual void handleEvent(gameObjectEvent ev) {};
	Bomb(Ogre::SceneNode* _node, Ogre::SceneManager* _msm, Vector3 position);
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	void explode();
	bool comprobarColision();
	~Bomb();
};

