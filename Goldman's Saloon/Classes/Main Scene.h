#pragma once
#include "HelloWorldScene.h"
#include "Player.h"
#include "Table.h"
#include "Enemy.h"
class CameraTracker;
class MainScene : public HelloWorld {
public:

	bool init();
	void update(float dt);
	void DPadCameraMovement();
	void backgroundSwitch();

	CREATE_FUNC(MainScene);
	
	Sedna::Player* playerOne;

	//dunno if we should actually use these
	std::vector<Sedna::Table*> tables;
	std::vector<Sedna::Outlaw*> outlaws;

	Background* bg1;
	Background* bg2;
	CameraTracker* cameraTracker;
};

class CameraTracker : public Sedna::GameObject {
public:
	CameraTracker(cocos2d::Scene* scene,const cocos2d::Vec2& LOCATION);
	void update(float dt) override;
	void die();
};
