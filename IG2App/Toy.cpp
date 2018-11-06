#include "Toy.h"
#include <iostream>

using namespace Ogre;
Toy::Toy(Ogre::SceneNode* _node, Ogre::SceneManager* _msm): gameObject(_node)
{
	
	nodeCuello = _node;
	nodeCuello->setScale(1, 1, 1);
	nodeCuello->setPosition(0, 0, 0);

	//Crea las entidades y los nodos del cuerpo
	Ogre::Entity* entCuerpo =_msm->createEntity("cuerpoToy", "sphere.mesh");//Cuerpo como hijo del cuello
	nodeCuerpo = nodeCuello->createChildSceneNode("nCuerpo");
	nodeCuerpo->attachObject(entCuerpo);
	nodeCuerpo->setScale(1, 1, 1);

	//Ombligo hijo del cuerpo
	Ogre::Entity* entOmb = _msm->createEntity("ombligoToy","sphere.mesh");
	nodeOmbligo = nodeCuerpo->createChildSceneNode("nOmbligo", { 0.0,0.0,100.0 });
	nodeOmbligo->attachObject(entOmb);
	nodeOmbligo->setScale(0.2, 0.2, 0.2);

	//Cabeza como hijo del cuello
	Ogre::Entity* entCabeza = _msm->createEntity("cabezaToy","sphere.mesh");
	nodeCabeza = nodeCuello->createChildSceneNode("nCabeza", { 0.0,150.0,0.0 });
	nodeCabeza->attachObject(entCabeza);
	nodeCabeza->setScale(0.5, 0.5, 0.5);

	//Nariz hija de la cabeza
	Ogre::Entity* entNariz = _msm->createEntity("narizToy","sphere.mesh");
	nodeNariz = nodeCabeza->createChildSceneNode("nNariz", { 0.0,0.0,100.0 });
	nodeNariz->attachObject(entNariz);
	nodeNariz->setScale(0.2, 0.2, 0.2);

	//Boca hija de la cabeza
	Ogre::Entity* entBoca = _msm->createEntity("bocaToy","sphere.mesh");
	nodeBoca = nodeCabeza->createChildSceneNode("nBoca", { 0.0,-50.0,100.0 });
	nodeBoca->attachObject(entBoca);
	nodeBoca->setScale(0.4, 0.1, 0.2);

	//OjoI hija de la cabeza
	Ogre::Entity* entOjoI = _msm->createEntity("ojoIToy","sphere.mesh");
	nodeOjoI = nodeCabeza->createChildSceneNode("nOjoI", { -50.0,50.0,100.0 });
	nodeOjoI->attachObject(entOjoI);
	nodeOjoI->setScale(0.2, 0.2, 0.2);

	//Ojo hija de la cabeza
	Ogre::Entity* entOjoD = _msm->createEntity("ojoDToy","sphere.mesh");
	nodeOjoD = nodeCabeza->createChildSceneNode("nOjoD", { 50.0,50.0,100.0 });
	nodeOjoD->attachObject(entOjoD);
	nodeOjoD->setScale(0.2, 0.2, 0.2);

}



void Toy::muere()
{
	nodeCuello->getCreator()->destroyEntity("cuerpoToy");
	nodeCuello->getCreator()->destroyEntity("cabezaToy");
	nodeCuello->getCreator()->destroyEntity("ojoIToy");
	nodeCuello->getCreator()->destroyEntity("ojoDToy");
	nodeCuello->getCreator()->destroyEntity("narizToy");
	nodeCuello->getCreator()->destroyEntity("ombligoToy");
	nodeCuello->getCreator()->destroyEntity("bocaToy");
	//nodeCuello->removeAndDestroyAllChildren();
	
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	if (evt.keysym.sym == SDLK_t) {
		nodeCuello->translate({ 0.0,0.0,3.0 }, Ogre::Node::TS_LOCAL);
		nodeCabeza->yaw(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
		nodeCuerpo->pitch(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_y) {
		switchParado();
	}
	else if (evt.keysym.sym == SDLK_v) {
		nodeCuello->yaw(Ogre::Radian(3.1415/4));
	}
	return true;
}
void Toy::handleEvent(gameObjectEvent ev)
{
	switch (ev) {
	case BOMBAEXPLOTA:
		muere();
		break;
	}
}
void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (!parado) {
		//Desplazamiento automático
		float aux = evt.timeSinceLastFrame;
		nodeCuello->translate({ 0.0,0.0,300.0f * aux }, Ogre::Node::TS_LOCAL);
		nodeCabeza->yaw(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
		nodeCuerpo->pitch(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
	}
	//evt.timeSinceLastFrame
	//evt.timeSinceLastEvent
}


Toy::~Toy()
{
}
