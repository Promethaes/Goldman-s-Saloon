#pragma once
#include "Projectile.h"
#include "XinputManager.h"
namespace Sedna {
	class Player : public GameObject {
	public:
		Player(XinputController* CONTROLLER, const char* path, cocos2d::Scene* scene,const cocos2d::Vec2 &LOCATION = cocos2d::Vec2(20, 20), float RADIUS = 10);

		void update(float dt) override;
	private:
		void shoot(float dt);
		void checkList();
		void checkInput();

		float gunTimer = 0.0f;
		bool hasShot = false;
		std::vector<Projectile*> pProjectiles;


		XinputController* pController;
		Stick pSticks[2];
		Triggers pTriggers;
	};
}