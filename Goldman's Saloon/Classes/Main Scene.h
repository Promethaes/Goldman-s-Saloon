#pragma once
#include "HelloWorldScene.h"
#include "Player.h"
#include "Table.h"
class MainScene : public HelloWorld {
public:

	bool init();
	void update(float dt);

	CREATE_FUNC(MainScene);
	
	Sedna::Player* playerOne;
	std::vector<Sedna::Table*> tables;
};