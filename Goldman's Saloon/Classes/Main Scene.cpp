#include "Main Scene.h"

bool MainScene::init()
{
	if (!HelloWorld::init())
	{
		return false;
	}

	playerOne = new Sedna::Player(p1Controller, "HelloWorld.png",this);

	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	manager.update();
	p1Controller->updateSticks(p1Sticks);
	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++) {
		Sedna::GameObject::gameObjects[i]->update(dt);
	}

}
