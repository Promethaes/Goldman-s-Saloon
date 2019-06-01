#pragma once
#include "GameObject.h"

namespace Sedna {
	class Table : public GameObject {
	public:
		Table(cocos2d::Scene* scene, const cocos2d::Vec2 &LOCATION, float RADIUS = 30);
		void update(float dt) override;
	private:
	};
}