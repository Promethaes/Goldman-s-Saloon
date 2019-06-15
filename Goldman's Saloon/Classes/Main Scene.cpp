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
	outlaws.push_back(new Sedna::Outlaw(this, cocos2d::Vec2(300, 200)));
	outlaws.push_back(new Sedna::ShotgunOutlaw(this, cocos2d::Vec2(300, 100)));
	outlaws.push_back(new Sedna::Rifleman(this, cocos2d::Vec2(200, 100)));

	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	manager.update();
	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);

	//kill stuff when it should die
	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++) {
		if (GameObjects[i]->hp <= 0) {
			GameObjects[i]->die();

			GameObjects.erase(GameObjects.begin() + i);
			i--;
		}
	}

	//collision and updating
	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++) {

		for (int j = 0; j < Sedna::GameObject::gameObjects.size(); j++) {
			if (i == j)
				continue;
			if (GameObjects[i]->id == "Player" && GameObjects[j]->id != "Player" && GameObjects[i]->hitbox->checkCollision(*GameObjects[j]->hitbox))
				GameObjects[i]->hitbox->setLocation(GameObjects[i]->hitbox->getLocation() - GameObjects[i]->hitbox->getVelocity());
		}
		Sedna::GameObject::gameObjects[i]->update(dt);

	}


}
