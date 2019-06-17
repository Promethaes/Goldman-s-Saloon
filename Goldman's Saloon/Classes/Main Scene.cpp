#include "Main Scene.h"
#include "Primitive.h"
#define GameObjects Sedna::GameObject::gameObjects
#define CAMERASPEED 1.0f
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

	bg1 = new Background("bg1.png", this);
	bg2 = new Background("bg2.png", this);
	bg2->sprite->setPosition(bg2->sprite->getPosition().x, bg2->sprite->getContentSize().height - 30);

	//hold the difference betweeen the two screens
	cameraTracker = new CameraTracker(this, bg2->sprite->getPosition());

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

	backgroundSwitch();



	//kill stuff when it should die
	for (int i = 0; i < Sedna::GameObject::gameObjects.size(); i++)
		if (GameObjects[i]->hp <= 0) {
			GameObjects[i]->die();

			GameObjects.erase(GameObjects.begin() + i);
			i--;
		}


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

void MainScene::backgroundSwitch()
{
	this->getDefaultCamera()->setPosition(this->getDefaultCamera()->getPosition() + cocos2d::Vec2(0, CAMERASPEED));

	//background changing code!! GREAT SUCCESS
	if (cameraTracker->hitbox->getLocation().y - bg1->sprite->getPosition().y >= 290 * 2) {
		bg1->sprite->setTexture("bg2.png");
		bg1->sprite->setPosition(bg1->sprite->getPosition() + cocos2d::Vec2(0, 290 * 2));
	}


	if (cameraTracker->hitbox->getLocation().y - bg2->sprite->getPosition().y >= 290 * 2)
		bg2->sprite->setPosition(bg2->sprite->getPosition() + cocos2d::Vec2(0, 290 * 2));

}

CameraTracker::CameraTracker(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION)
	:GameObject("crosshairs.png", scene, LOCATION, 1)
{
	id = "CAMERA";
	hp = INT_MAX;
}

void CameraTracker::update(float dt)
{
	hitbox->setLocation(hitbox->getLocation() + cocos2d::Vec2(0, CAMERASPEED));
	updateGO(dt);
}

void CameraTracker::die()
{
}
