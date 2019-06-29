#pragma once
#include "GameObject.h"
#include "cocos2d.h"
//change in ui as well if you change it here
#define CAMERASPEED 1.0f

namespace Sedna {

	class Background {
	public:
		Background(const char* path, cocos2d::Scene* scene);
		cocos2d::Sprite* sprite;
	};

	//the DDOS
	class CameraTracker : public Sedna::GameObject {
	public:
		CameraTracker(cocos2d::Scene* scene, const cocos2d::Vec2& LOCATION);
		void update(float dt) override;
		void die();
		void backgroundSwitch();
		Background* bg1;
		Background* bg2;

		bool stop = false;
	};
}