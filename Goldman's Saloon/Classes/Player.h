#pragma once
#include "GameObject.h"
#include "XinputManager.h"
namespace Sedna {
	class Gun;
	class Player : public GameObject {
	public:
		Player(XinputController* CONTROLLER, const char* path, cocos2d::Scene* scene,const cocos2d::Vec2 &LOCATION = cocos2d::Vec2(20, 20), float RADIUS = 20);

		void update(float dt) override;
		Stick pSticks[2];
		void setGun(Gun* gun) { currentGun = gun; }
		void die() override;
	private:
		bool kickTables();
		void shoot(float dt);
		void checkList();
		void checkInput();
		void checkProjectileCollision();

		float gunTimer = 0.0f;
		bool hasShot = false;
		Gun* currentGun;
		

		XinputController* pController;
		Triggers pTriggers;
	};
}