#include "Toy.h"



Toy::Toy(Ogre::SceneNode* nodeMain)
{
	this->nodeMain = nodeMain;
	
	nodeCuello= nodeMain->createChildSceneNode("nCuello");//Cuello como hijo del plano
	nodeCuello->setScale(1, 1, 1);
	nodeCuello->setPosition(0, 0, 0);

	Ogre::Entity* entCuerpo = nodeMain->getCreator()->createEntity("sphere.mesh");//Cuerpo como hijo del cuello
	nodeCuerpo = nodeCuello->createChildSceneNode("nCuerpo");
	nodeCuerpo->attachObject(entCuerpo);
	nodeCuerpo->setScale(1, 1, 1);

	//Ombligo hijo del cuerpo
	Ogre::Entity* entOmb = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeOmbligo = nodeCuerpo->createChildSceneNode("nOmbligo", { 0.0,0.0,100.0 });
	nodeOmbligo->attachObject(entOmb);
	nodeOmbligo->setScale(0.2, 0.2, 0.2);

	//Cabeza como hijo del cuello
	Ogre::Entity* entCabeza = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeCabeza = nodeCuello->createChildSceneNode("nCabeza", { 0.0,150.0,0.0 });
	nodeCabeza->attachObject(entCabeza);
	nodeCabeza->setScale(0.5, 0.5, 0.5);

	//Nariz hija de la cabeza
	Ogre::Entity* entNariz = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeNariz = nodeCabeza->createChildSceneNode("nNariz", { 0.0,0.0,100.0 });
	nodeNariz->attachObject(entNariz);
	nodeNariz->setScale(0.2, 0.2, 0.2);

	//Boca hija de la cabeza
	Ogre::Entity* entBoca = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeBoca = nodeCabeza->createChildSceneNode("nBoca", { 0.0,-50.0,100.0 });
	nodeBoca->attachObject(entBoca);
	nodeBoca->setScale(0.4, 0.1, 0.2);

	//OjoI hija de la cabeza
	Ogre::Entity* entOjoI = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeOjoI = nodeCabeza->createChildSceneNode("nOjoI", { -50.0,50.0,100.0 });
	nodeOjoI->attachObject(entOjoI);
	nodeOjoI->setScale(0.2, 0.2, 0.2);

	//Ojo hija de la cabeza
	Ogre::Entity* entOjoD = nodeMain->getCreator()->createEntity("sphere.mesh");
	nodeOjoD = nodeCabeza->createChildSceneNode("nOjoD", { 50.0,50.0,100.0 });
	nodeOjoD->attachObject(entOjoD);
	nodeOjoD->setScale(0.2, 0.2, 0.2);

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
void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (!parado && evt.timeSinceLastFrame <= 1) {
		nodeCuello->translate({ 0.0,0.0,3.0 }, Ogre::Node::TS_LOCAL);
		nodeCabeza->yaw(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
		nodeCuerpo->pitch(Ogre::Radian(0.1), Ogre::Node::TS_LOCAL);
	}
	//evt.timeSinceLastFrame
	//evt.timeSinceLastEvent
}


Toy::~Toy()
{
}
