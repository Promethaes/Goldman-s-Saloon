#pragma once
#include "GameObject.h"

namespace Sedna {
	class Projectile;
	class Outlaw : public GameObject {
	public:
		Outlaw(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION, const char* path = "outlawLl.png", float RADIUS = 20);
		void update(float dt) override;

		void die() override;
		void shoot(float dt);
	private:
		void checkList();

		float gunTimer = 0.0f;
		bool hasShot = false;
		std::vector<Projectile*> eProjectiles;
	};
}