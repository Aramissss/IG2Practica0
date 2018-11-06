#pragma once
#include "gameObject.h"
#include <OgreEntity.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreAnimationState.h>
#include <OgreQuaternion.h>
#include <iostream>
enum SinbadState { RUN, DANCE , MOVTOBOMB, DEATH};
class Sinbad :
	public gameObject
{
private:
	
	Ogre::Entity* ent;
	Ogre::SceneNode* mSinbadNode = nullptr;
	Ogre::AnimationState* animStateDance;
	Ogre::AnimationState* animStateRunTop;
	Ogre::AnimationState* animStateRunBot;
	Ogre::AnimationState* animStateMovimiento;
	Ogre::AnimationState* animStateMovToBomb;
	Ogre::AnimationState* animStateSliceSwords;
	Ogre::AnimationState* animStateDeath;
	Ogre::Animation* animMovToBomb;
	Ogre::Animation* animDeath;
	SinbadState sinbadState;
	Ogre::Entity* swordI;
	Ogre::Entity* swordD;
public:
	//Ogre::SceneNode* getMainNode() { return mSinbadNode; };
	Sinbad(Ogre::SceneNode* _node, Ogre::SceneManager* _msm);
	void creaAnimaciones();
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);
	virtual void handleEvent(gameObjectEvent ev);
	void moveToBomb();
	~Sinbad();
};

