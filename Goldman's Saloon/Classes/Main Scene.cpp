#include "Main Scene.h"
#include "Primitive.h"
#include "CameraTracker.h"
#define GameObjects Sedna::GameObject::gameObjects
bool MainScene::init()
{
	if (!HelloWorld::init())
	{
		return false;
	}

	//all of the enemies are in for testing purposes
	playerOne = new Sedna::Player(p1Controller, "player1.png", this);
	tables.push_back(new Sedna::Table(this, cocos2d::Vec2(200, 200)));
	outlaws.push_back(new Sedna::Outlaw(this, cocos2d::Vec2(300, 200)));
	outlaws.push_back(new Sedna::ShotgunOutlaw(this, cocos2d::Vec2(300, 100)));
	outlaws.push_back(new Sedna::Rifleman(this, cocos2d::Vec2(200, 100)));
	outlaws.push_back(new Sedna::CrazyPete(this, cocos2d::Vec2(100, 250)));


	auto bg2 = new Sedna::Background("bg2.png", this);
	cameraTracker = new Sedna::CameraTracker(this, cocos2d::Vec2(bg2->sprite->getPosition().x, bg2->sprite->getContentSize().height - 30));
	bg2->sprite->removeFromParent();



	//hold the difference betweeen the two screens
	//290
//	std::cout << hold.y;

	this->scheduleUpdate();

	return true;
}

void MainScene::update(float dt)
{
	manager.update();
	p1Controller->updateSticks(p1Sticks);
	p1Controller->getTriggers(p1Triggers);

#ifdef _DEBUG
	//check to see if the camera should move
	DPadCameraMovement();
#endif

	
	this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, CAMERASPEED));



	//kill stuff when it should die
	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++)
		if (GameObjects[i]->hp <= 0) {
			GameObjects[i]->die();

			GameObjects.erase(GameObjects.begin() + i);
			i--;
		}

	//could handle this internally, probably a good idea not to since this checks if:
	//on the previous update, the player held LT. if they did, then activate bulletTime on all game objects
	//if handled internally, this would make the player 1 update ahead of all the other game objects, since this would be inside
	//its update function.
	if (p1Triggers.LT > 0)
		for (int i = 0; i < GameObjects.size(); i++)
			GameObjects[i]->activateBulletTime();

	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++)
		Sedna::GameObject::gameObjects[i]->update(dt);


	//dt /= 2;



}

void MainScene::DPadCameraMovement()
{
	if (p1Controller->isButtonPressed(Sedna::DPAD_UP))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, 1.0f));
	if (p1Controller->isButtonPressed(Sedna::DPAD_DOWN))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, -1.0f));
	if (p1Controller->isButtonPressed(Sedna::DPAD_LEFT))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(-1.0f, 0));
	if (p1Controller->isButtonPressed(Sedna::DPAD_RIGHT))
		this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(1.0f, 0));

}




