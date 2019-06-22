#pragma once
#include "GameObject.h"
namespace Sedna {
	
	class Projectile : public GameObject {
	public:
		Projectile(const char* path, cocos2d::Scene* scene, const cocos2d::Vec2 &LOCATION, float RADIUS);
		
		void update(float dt) override;
		void die() override;
	private:
	};
}