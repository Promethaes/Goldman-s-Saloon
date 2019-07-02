#pragma once
#include "GameObject.h"
#include "XinputManager.h"
#include "UI.h"
namespace Sedna {
	class Gun;
	class Player : public GameObject {
	public:
		Player(XinputController* CONTROLLER, const char* path, cocos2d::Scene* scene, unsigned playerNumber = 1, const cocos2d::Vec2 &LOCATION = cocos2d::Vec2(20, 20), float RADIUS = 20);

		void update(float dt) override;
		void setGun(Gun* gun) { currentGun = gun; }
		Gun* getGun() const { return currentGun; }
		void die() override;
		unsigned getPlayerNumber() const { return playerNumber; }
		unsigned getScore() const { return score; }

		bool invincible = false;
		Stick pSticks[2];
	private:
		PlayerUI* pUi;
		void checkCollision(float dt);
		bool kickTables();
		void shoot(float dt);
		void checkList();
		void checkInput();
		void checkProjectileCollision();

		float gunTimer = 0.0f;
		bool hasShot = false;
		Gun* currentGun;
		
		unsigned score = 0;
		unsigned playerNumber;
		float invincibilityTimer = 5.0f;//subject to change

		XinputController* pController;
		Triggers pTriggers;
	};
}