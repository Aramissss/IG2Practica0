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

PlaneObject::PlaneObject(Ogre::SceneNode* _node) : gameObject(_node)
{
	

	entPlane = _node->getCreator()->createEntity("mPlane1080x800");
	entPlane->setMaterialName("WaterMaterial/plano");
	
	mPlaneNode = _node->createChildSceneNode("mPlane1080x800");
	mPlaneNode->attachObject(entPlane);

}
void PlaneObject::crearReflejo(Camera* camRef) {

	TexturePtr rttTex = TextureManager::getSingleton().createManual("textRtt",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D, 600,
		600,
		0, PF_R8G8B8, TU_RENDERTARGET);
	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef);
	renderTexture->addListener(this);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	TextureUnitState* tu = entPlane->getSubEntities()[0]->getMaterial()->
		getTechniques()[0]->getPasses()[0]->createTextureUnitState("textRtt");

	tu->setColourOperation(LBO_ADD);
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	tu->setProjectiveTexturing(true, camRef);

}
bool PlaneObject::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_p) {
		mPlaneNode->pitch(Ogre::Radian(0.1));
	}
	return true;
}

void PlaneObject::preRenderTargetUpdate(const Ogre::RenderTargetEvent & evt)
{
	entPlane->setVisible(false);
}

void PlaneObject::postRenderTargetUpdate(const Ogre::RenderTargetEvent & evt)
{
	entPlane->setVisible(true);
}


PlaneObject::~PlaneObject()
{
}
