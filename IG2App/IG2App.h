#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Toy.h"
#include "Sinbad.h"
#include "PlaneObject.h"
#include "Bomb.h"
#include "gameObject.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  bool sinbadFocus = false;
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSmokeNode = nullptr;
  Ogre::SceneNode* mBBNode = nullptr;
  //Ogre::SceneNode* mPlaneNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;
  Toy* mToy = nullptr;
  Sinbad* mSinbad = nullptr;
  PlaneObject* mPlane = nullptr;
  Bomb* mBomb = nullptr;
};

#endif
