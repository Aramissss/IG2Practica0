#include "Bomb.h"
#include <iostream>
#include "PlaneObject.h"
#include <OgreEntity.h>
using namespace Ogre;

Bomb::Bomb(Ogre::SceneNode* _node, Ogre::SceneManager* _msm, Vector3 position): gameObject(_node)
{
	mBombNode = _node;
	ent = _msm->createEntity("bomba","uv_sphere.mesh");
	ent->setMaterialName("IG2App/Bomb");	

	//Crea el sistema de humo pero no emite partículas hasta que explota
	smoke = _msm->createParticleSystem("parSys", "Examples/SmokeParticle");
	mBombNode->getParentSceneNode()->attachObject(smoke);
	smoke->setEmitting(false);
	
	mBombNode->setScale(0.2,0.2 , 0.2);
	mBombNode->setInitialState();
	mBombNode->setPosition(position);


	//Crea la animación de la bomba flotando
	Real duracion = 16.0;

	Animation* animation = _msm->createAnimation("AnimVV", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mBombNode);
	Vector3 keyframePos(mBombNode->getPosition());
	
	Real longitudPaso = duracion / 4.0;

	TransformKeyFrame* kf;
	
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setTranslate(keyframePos);

	animationState = _msm->createAnimationState("AnimVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);

	float tamDesplazamiento = 20.0f;
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

	mBombNode->attachObject(ent);
}
bool Bomb::comprobarColision()
{
	//Acede a las bounding sphere del cuerpo de toy y de la bomba para comprobar colisiones
	SceneNode* ncuerpo = mBombNode->getCreator()->getSceneNode("nCuerpo");
	Sphere cuerpoSphere = ncuerpo->getAttachedObject("cuerpoToy")->getWorldBoundingSphere();
	SceneNode* nbomba = mBombNode->getCreator()->getSceneNode("nBomb");
	Sphere bombaSphere = nbomba->getAttachedObject("bomba")->getWorldBoundingSphere();
	if (bombaSphere.intersects(cuerpoSphere)) {
		return true;
	}
	return false;
}
void Bomb::frameRendered(const Ogre::FrameEvent & evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
	if (!exploded && comprobarColision()) explode();//Si colisionan la bomba explota
}
bool Bomb::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_b) {
		explode();
	}
	return true;
}

void Bomb::explode()
{
	if (!exploded) {//Cuando explota emite las partículas y envía el mensaje a todos los listeners
		smoke->setEmitting(true);
		mBombNode->getCreator()->destroyEntity(ent);
		fireAppEvent(gameObjectEvent::BOMBAEXPLOTA);
		exploded = true;
	}
}


Bomb::~Bomb()
{
}
