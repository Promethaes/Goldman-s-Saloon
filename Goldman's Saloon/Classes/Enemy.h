#pragma once
#include "Guns.h"

namespace Sedna {
	//base outlaw
	class Outlaw : public GameObject {
	public:
		Outlaw(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION, const char* path = "outlawLl.png", float RADIUS = 20,Gun* CURRENTGUN = new olReliable());
		void update(float dt) override;


		void die() override;
	private:
		void checkProjectileCollision();
		void checkList();
	protected:
		Gun* currentGun;

	};

	class ShotgunOutlaw : public Outlaw {
	public:
		ShotgunOutlaw(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION, const char* path = "shotgunOutlaw.png");
		
		//override is required, as otherwise this class will not be able to be able to produce objects due to how abstract classes work
		void die() override;
		
		
	};
}