#include "PlaneObject.h"
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

PlaneObject::PlaneObject(Ogre::SceneNode* _parentNode) : gameObject(_parentNode)
{
	

	entPlane = _parentNode->getCreator()->createEntity("mPlane1080x800");
	entPlane->setMaterialName("WaterMaterial/plano");
	mPlaneNode = _parentNode->createChildSceneNode("mPlane1080x800");
	mPlaneNode->attachObject(entPlane);


	mainNode = mPlaneNode;
	crearReflejo();
}
void PlaneObject::crearReflejo() {


	Ogre::Camera* camRef = mainNode->getCreator()->createCamera("RefCam");
	MovablePlane* mp = new MovablePlane({ 0.0f,0.0f,0.0f }, 0.0f);
	mainNode->attachObject(mp);
	camRef->enableReflection(mp);
	camRef->enableCustomNearClipPlane(mp);
	TexturePtr rttTex = TextureManager::getSingleton().createManual("texRtt",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D, (Real)500,
		(Real)camRef->getViewport()->getActualHeight(),
		0, PF_R8G8B8, TU_RENDERTARGET);
	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	TextureUnitState* tu = entPlane->getSubEntities()[0]->getMaterial()->
		getTechniques()[0]->getPasses()[0]->createTextureUnitState("textRtt");

	tu->setColourOperation(LBO_MODULATE);
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	tu->setProjectiveTexturing(true, camRef);

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
