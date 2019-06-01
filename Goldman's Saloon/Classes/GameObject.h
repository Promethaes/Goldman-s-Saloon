#pragma once
#include "cocos2d.h"
#include <vector>
namespace Sedna {
	class CirclePrimitive;
	class GameObject {
	public:
		GameObject(const char* path, cocos2d::Scene* scene, const cocos2d::Vec2 &LOCATION, float RADIUS, bool pushback = true, float ANGLE = 5, unsigned int SEGMENTS = 50);
		void updateGO(float dt);
		///<every single game object should have its own update that calls updateGO>
		virtual void update(float dt) = 0;

		static std::vector<GameObject*> gameObjects;
		CirclePrimitive* hitbox;
		cocos2d::Sprite* sprite;
	protected:
		cocos2d::Scene* scene;
	};
}