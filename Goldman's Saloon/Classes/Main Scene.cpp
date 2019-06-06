#include "Main Scene.h"
#include "Primitive.h"
#define GameObjects Sedna::GameObject::gameObjects
bool MainScene::init()
{
	if (!HelloWorld::init())
	{
		return false;
	}

	playerOne = new Sedna::Player(p1Controller, "player1.png", this);
	tables.push_back(new Sedna::Table(this, cocos2d::Vec2(200, 200)));


	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	manager.update();
	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);

	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++)
		for (int j = 0; j < Sedna::GameObject::gameObjects.size(); j++) {
			if (i == j)
				continue;
			if (GameObjects[i]->id == "Player" && GameObjects[j]->id != "Player" && GameObjects[i]->hitbox->checkCollision(*GameObjects[j]->hitbox)) {
				//auto norm = GameObjects[i]->hitbox->getVelocity() / sqrt(GameObjects[i]->hitbox->getVelocity().x*GameObjects[i]->hitbox->getVelocity().x + GameObjects[i]->hitbox->getVelocity().y*GameObjects[i]->hitbox->getVelocity().y);

				auto distance = cocos2d::Vec2(GameObjects[i]->hitbox->getLocation() - GameObjects[j]->hitbox->getLocation());

				GameObjects[i]->hitbox->setLocation(GameObjects[i]->hitbox->getLocation() - GameObjects[i]->hitbox->getVelocity());
			//	GameObjects[i]->hitbox->setForce(distance * 2);

				/////GameObjects[i]->hitbox->setForce(-norm*250);
				/////send it back in time 10 frames?!?
				///GameObjects[i]->hitbox->dt += 10*dt;
			}


		}


	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++)
		Sedna::GameObject::gameObjects[i]->update(dt);

}
