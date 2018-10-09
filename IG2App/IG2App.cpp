#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMovablePlane.h>
#include <OgreMeshManager.h>
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreTexture.h>
#include <OgreRenderTexture.h>
#include <OgreTechnique.h>
#include <OgreCompositionTargetPass.h>
#include <OgrePass.h>
#include <OgreSubEntity.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  
  //else if (evt.keysym.sym == SDLK_???)
  
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  //mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
  //------------------------------------------------------------------------

  //Creación plano
  MeshManager::getSingleton().createPlane("mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, -Vector3::UNIT_Z);

  mPlane = new PlaneObject(mSM->getRootSceneNode());

  addInputListener(mPlane);
  
  //------------------------------------------------------------------------
 // mToyNode = new Toy(mPlaneNode, mSM);
 

  //camRef->setNearClipDistance(1);
  //camRef->setFarClipDistance(10000);
  //camRef->setAutoAspectRatio(true);
  //camRef->enableReflection(mPlaneNode);
  //camRef->enableCustomNearClipPlane(mPlaneNode)
	  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	/*  Ogre::SceneNode* mCamNode = nullptr;
  mCamNode = _parentNode->getCreator()->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(camRef);*/

 
  //------------------------------------------------------------------------

  // finally something to render
  Sinbad* mSinbad = new Sinbad(mPlane->getMainNode());

  addInputListener(mSinbad);

  mToy = new Toy(mPlane->getMainNode());
  mToy->setPosition({ 0, 100, -300 });

  addInputListener(mToy);
  

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);
}

