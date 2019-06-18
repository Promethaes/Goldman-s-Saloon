#pragma once
#include "HelloWorldScene.h"
#include "Player.h"
#include "Table.h"
#include "Enemy.h"
#include "CameraTracker.h"
//forward declarations
//lul there are none

class MainScene : public HelloWorld {
public:

	bool init();
	void update(float dt);
	void DPadCameraMovement();

	CREATE_FUNC(MainScene);
	
	Sedna::Player* playerOne;

	//dunno if we should actually use these
	std::vector<Sedna::Table*> tables;
	std::vector<Sedna::Outlaw*> outlaws;

	Sedna::CameraTracker* cameraTracker;
};


