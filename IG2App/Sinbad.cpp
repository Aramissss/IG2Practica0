#include "Sinbad.h"
#include <iostream>
#include <OgreSkeleton.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreBone.h>
using namespace Ogre;

Sinbad::Sinbad(Ogre::SceneNode* _node, Ogre::SceneManager* _msm): gameObject(_node)
{
	ent = _msm->createEntity("Sinbad.mesh");
	mSinbadNode = _node;
	_node->setScale(20, 20, 20);
	mSinbadNode->setInitialState();
	_node->setPosition(500, 100,-300);
	
	//Crea las espadas y las une a Sinbad
	swordI = _msm->createEntity("Sword.mesh");//Crea las entidades de las espadas
	swordD = _msm->createEntity("Sword.mesh");
	ent->attachObjectToBone("Handle.R", swordD);//Una la espada a su mano
	ent->attachObjectToBone("Sheath.L", swordI);


	creaAnimaciones();
	mSinbadNode->attachObject(ent);//Añade la entidad de sinbad al nodo
	

}
void Sinbad::creaAnimaciones() {
	

	Ogre::SceneManager* _msm = mSinbadNode->getCreator();
	//Crea las animaciones predefinidas
	animStateDance = ent->getAnimationState("Dance");//Crea las animationState
	animStateRunTop = ent->getAnimationState("RunTop");
	animStateRunBot = ent->getAnimationState("RunBase");
	animStateSliceSwords = ent->getAnimationState("SliceHorizontal");

	
	sinbadState = RUN;//Estado inicial

	animStateRunTop->setEnabled(true);//Empieza con el estado de baile
	animStateRunBot->setEnabled(true);//Empieza con el estado de baile
	animStateSliceSwords->setEnabled(false);
	animStateRunTop->setLoop(true);
	animStateRunBot->setLoop(true);
	animStateSliceSwords->setLoop(true);

	//Creación animación desplazamiento en rectángulo
	Real duracion = 16.0;

	Animation* animation = _msm->createAnimation("RectangleMov", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mSinbadNode);
	Vector3 keyframePos(mSinbadNode->getPosition());
	Real longitudPaso = duracion / 8.0;


	animStateMovimiento = _msm->createAnimationState("RectangleMov");
	animStateMovimiento->setLoop(true);
	animStateMovimiento->setEnabled(true);

	float tamLargo = 600.0f;
	float tamAncho = 1000.0f;
	TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, 1))));
	kf->setTranslate(keyframePos);

	//Se mueve hacie abajo
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Z*tamLargo;
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, 1))));
	kf->setTranslate(keyframePos);

	//Gira a la izquierda
	kf = track->createNodeKeyFrame(longitudPaso * 2);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0))));
	kf->setTranslate(keyframePos);

	//Se mueve hacia la izquierda
	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X*tamAncho;
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0))));
	kf->setTranslate(keyframePos);

	//Gira hacia arriba
	kf = track->createNodeKeyFrame(longitudPaso * 4);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1))));
	kf->setTranslate(keyframePos);

	//Se mueve hacie arriba
	kf = track->createNodeKeyFrame(longitudPaso * 5);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z*tamLargo;
	kf->setTranslate(keyframePos);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1))));

	//Gira a la derecha
	kf = track->createNodeKeyFrame(longitudPaso * 6);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0))));
	kf->setTranslate(keyframePos);

	//Se mueve hacia la derecha
	kf = track->createNodeKeyFrame(longitudPaso * 7);
	keyframePos += Ogre::Vector3::UNIT_X*tamAncho;
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0))));
	kf->setTranslate(keyframePos);

	//Gira hacia abajo
	kf = track->createNodeKeyFrame(longitudPaso * 8);
	kf->setRotation((Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, 1))));
	kf->setTranslate(keyframePos);


	//CREA ANIMACIÓN DE DESPLAZAMIENTO HACIA LA BOMBA PERO NO DEFINE SUS POSICIONES
	//Las posiciones se definen una vez ha explotado la bomba
	duracion = 1.0;
	animMovToBomb = mSinbadNode->getCreator()->createAnimation("MovToBomb", duracion);

	NodeAnimationTrack* track2 = animMovToBomb->createNodeTrack(1);
	track2->setAssociatedNode(mSinbadNode);
	Vector3 keyframePos2(mSinbadNode->getPosition());
	keyframePos2 = mSinbadNode->getPosition();
	animStateMovToBomb = mSinbadNode->getCreator()->createAnimationState("MovToBomb");
	TransformKeyFrame* kf1;
	kf1 = track2->createNodeKeyFrame(0);

	kf1 = track2->createNodeKeyFrame(1);

	//Crea la animación de cuando está muerto	
	duracion = 10;
	animDeath = _msm->createAnimation("Death", duracion);
	NodeAnimationTrack* track3 = animDeath->createNodeTrack(2);
	track3->setAssociatedNode(mSinbadNode);
	Vector3 keyframePos3(mSinbadNode->getPosition());

	animStateDeath = _msm->createAnimationState("Death");
	animStateDeath->setEnabled(false);

	TransformKeyFrame* kf2;
	kf2 = track3->createNodeKeyFrame(0);
	kf2 = track3->createNodeKeyFrame(10);
}
void Sinbad::frameRendered(const Ogre::FrameEvent & evt)
{
	//Dependiendo del estado actualiza las animaciones
	switch (sinbadState) {
	case RUN: {
		animStateMovimiento->addTime(evt.timeSinceLastFrame);
		animStateRunTop->addTime(evt.timeSinceLastFrame);
		animStateRunBot->addTime(evt.timeSinceLastFrame);
		break;
	}
	case DANCE: {
		animStateDance->addTime(evt.timeSinceLastFrame);
		break;
	}
	case MOVTOBOMB: {
		animStateMovToBomb->addTime(evt.timeSinceLastFrame);
		animStateSliceSwords->addTime(evt.timeSinceLastFrame);
		animStateRunBot->addTime(evt.timeSinceLastFrame);
		//Cuando termina la animación de moverse a la bomba activa el estado DEATH
		if (animStateMovToBomb->hasEnded()) {
			animStateMovToBomb->setEnabled(false);
			animStateDeath->setEnabled(true);
			animStateDeath->setLoop(false);

			//Actualiza la animación de muerte
			TransformKeyFrame* kf1;
			Vector3 keyframePos = mSinbadNode->getPosition();
			keyframePos.y = 0;
			kf1 = animDeath->getNodeTrack(2)->getNodeKeyFrame(0);
			kf1->setRotation(Ogre::Vector3::UNIT_Z.getRotationTo({ 0,1,0 }));
			kf1->setTranslate(keyframePos);

			keyframePos.x = 500;
			kf1 = animDeath->getNodeTrack(2)->getNodeKeyFrame(1);
			kf1->setRotation(Ogre::Vector3::UNIT_Z.getRotationTo({ 0,1,0 }));
			kf1->setTranslate(keyframePos);
			sinbadState = DEATH;
		}
		break;
	}
	case DEATH: {
		animStateDeath->addTime(evt.timeSinceLastFrame);
		
		break;
	}
	}
	
	
}
bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_r) {
		if (sinbadState != MOVTOBOMB && sinbadState!=DEATH) {
			if (sinbadState != RUN) {
				//Cuando corre tiene una espada envainada y otra en la mano
				ent->detachAllObjectsFromBone();
				ent->attachObjectToBone("Handle.R", swordD);
				ent->attachObjectToBone("Sheath.L", swordI);
				animStateRunTop->setEnabled(true);
				animStateRunBot->setEnabled(true);
				sinbadState = RUN;
			}
			else if (sinbadState != DANCE && sinbadState != DEATH) {
				//Baila con las dos espadas envainadas
				ent->detachAllObjectsFromBone();
				ent->attachObjectToBone("Handle.R", swordD);
				ent->attachObjectToBone("Handle.L", swordI);
				sinbadState = DANCE;
				animStateRunTop->setEnabled(false);
				animStateRunBot->setEnabled(false);
				animStateDance->setEnabled(true);
				animStateDance->setLoop(true);
			}
		}
	}
	else if (evt.keysym.sym == SDLK_0) {//Muestra animaciones de sinbad
		AnimationStateSet * aux = ent->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();
		while (it != aux->getAnimationStateIterator().end()) {
			auto s =
				it->first; ++it;
			std::cout << s <<std::endl;
		}
		std::cout << std::endl;
		auto skeleton = ent->getMesh()->getSkeleton(); // entity -> getMesh()
		auto numBones = skeleton->getNumBones();
		for (int i = 0; i < numBones;i++) { 
			std::cout << skeleton->getBone(i)->getName()<<std::endl;
		}
	}
	return true;
}

void Sinbad::handleEvent(gameObjectEvent ev)
{
	switch (ev) {
	case BOMBAEXPLOTA:
		moveToBomb();
		break;
	}
}

void Sinbad::moveToBomb()
{
	//Envaina las dos espadas
	ent->detachAllObjectsFromBone();
	ent->attachObjectToBone("Handle.R", swordD);
	ent->attachObjectToBone("Handle.L", swordI);
	sinbadState = MOVTOBOMB;
	animStateMovToBomb->setEnabled(true);
	animStateMovToBomb->setLoop(false);
	animStateMovimiento->setEnabled(false);
	animStateSliceSwords->setEnabled(true);
	TransformKeyFrame* kf1;

	//Define las posiciones del movimiento hacia la bomba

	Ogre::Quaternion rot = mSinbadNode->getOrientation();
	Vector3 keyframePos = mSinbadNode->getPosition();
	//Accede a la posición de la bomba a través del SceneManager
	Vector3 bombPos = mSinbadNode->getCreator()->getSceneNode("nBomb")->getPosition();
	bombPos.y = keyframePos.y;

	Vector3 dest = Vector3(bombPos - keyframePos);
	rot = Ogre::Vector3::UNIT_Z.getRotationTo(dest);

	kf1 = animMovToBomb->getNodeTrack(1)->getNodeKeyFrame(0);
	kf1->setRotation(rot);
	kf1->setTranslate(keyframePos);

	//En el segundo keyframe se desplaza a la posición de la bomba
	kf1 = animMovToBomb->getNodeTrack(1)->getNodeKeyFrame(1);
	rot = Ogre::Vector3::UNIT_Z.getRotationTo(dest);
	kf1->setRotation(rot);
	kf1->setTranslate(bombPos);


}

Sinbad::~Sinbad()
{
}
