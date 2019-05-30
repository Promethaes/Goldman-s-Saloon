#pragma once
#include "HelloWorldScene.h"
#include "Player.h"
class MainScene : public HelloWorld {
public:

	bool init();
	void update(float dt);

	CREATE_FUNC(MainScene);

	Sedna::Player* playerOne;

};