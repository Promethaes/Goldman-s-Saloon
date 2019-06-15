#pragma once
#include "HelloWorldScene.h"
#include "Player.h"
#include "Table.h"
#include "Enemy.h"
class MainScene : public HelloWorld {
public:

	bool init();
	void update(float dt);

	CREATE_FUNC(MainScene);
	
	Sedna::Player* playerOne;

	//dunno if we should actually use these
	std::vector<Sedna::Table*> tables;
	std::vector<Sedna::Outlaw*> outlaws;

	Background* bg1;
};