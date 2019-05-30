#pragma once
#include "GameObject.h"
#include "XinputManager.h"
namespace Sedna {
	class Player : public GameObject {
	public:
		Player(XinputController* CONTROLLER, const char* path, cocos2d::Scene* scene,const cocos2d::Vec2 &LOCATION = cocos2d::Vec2(20, 20), float RADIUS = 10);

		void update(float dt);
	private:
		void checkInput();
		XinputController* pController;
		Stick pSticks[2];
	};
}