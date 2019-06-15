#include "Main Scene.h"
#include "Primitive.h"
//#include <iostream>
#define GameObjects Sedna::GameObject::gameObjects
#define CAMERASPEED 1.0f
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
	outlaws.push_back(new Sedna::CrazyPete(this, cocos2d::Vec2(100, 250)));

	bg1 = new Background("bg1.png",this);
	//bg1->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
	//bg1->setScaleX(0.85f);
	//bg1->setScaleY(0.92f);
	//this->addChild(bg1, -1000);

	//std::cout << this->getDefaultCamera()->getPosition().y;
	//this->getDefaultCamera()->setPosition(cocos2d::Vec2(this->getDefaultCamera()->getPosition().x, 0));

	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	manager.update();
	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);


	if (p1Controller->isButtonPressed(Sedna::DPAD_UP))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, 1.0f));
	if (p1Controller->isButtonPressed(Sedna::DPAD_DOWN))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, -1.0f));
	if (p1Controller->isButtonPressed(Sedna::DPAD_LEFT))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(-1.0f, 0));
	if (p1Controller->isButtonPressed(Sedna::DPAD_RIGHT))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(1.0f, 0));

	//for (auto x : GameObjects)
	//	if (x->id == "Player")
	//		this->getDefaultCamera()->setPosition(x->hitbox->getLocation());


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
