#include "Bomb.h"

using namespace Ogre;

Bomb::Bomb(Ogre::SceneNode* _node, Ogre::SceneManager* _msm): gameObject(_node)
{
	mBombNode = _node;//Cuello como hijo del plano
	mBombNode->setScale(0.5, 0.5, 0.5);
	Entity* ent = _msm->createEntity("uv_sphere.mesh");
	ent->setMaterialName("IG2App/Bomb");
	mBombNode->attachObject(ent);

	Real duracion = 20;

	Animation* animation = _msm->createAnimation("AnimVV", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mBombNode);
	Vector3 keyframePos;
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

	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Y*tamDesplazamiento;
	kf->setTranslate(keyframePos);

}
void Bomb::frameRendered(const Ogre::FrameEvent & evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}


Bomb::~Bomb()
{
}
